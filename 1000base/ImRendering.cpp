#include "Main.h"

void __stdcall ImGuiRendering::CreateObjects(IDirect3DDevice9* pDevice)
{
	_drawList = new ImDrawList();

	auto font_path = std::string{};

	uint8_t* pixel_data;

	int width,
		height,
		bytes_per_pixel;

	auto font = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(_compressed_data_base85, 18);
	_fonts.GetTexDataAsRGBA32(&pixel_data, &width, &height, &bytes_per_pixel);

	auto hr = pDevice->CreateTexture(
		width, height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&_texture,
		NULL);

	if (FAILED(hr)) return;

	D3DLOCKED_RECT tex_locked_rect;
	if (_texture->LockRect(0, &tex_locked_rect, NULL, 0) != D3D_OK)
		return;
	for (int y = 0; y < height; y++)
		memcpy((uint8_t*)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixel_data + (width * bytes_per_pixel) * y, (width * bytes_per_pixel));
	_texture->UnlockRect(0);

	_fonts.TexID = _texture;
}

void __stdcall ImGuiRendering::InvalidateObjects()
{
	if (_texture) _texture->Release();
	_texture = nullptr;

	_fonts.Clear();

	if (_drawList)
		delete _drawList;
	_drawList = nullptr;
}

void __stdcall ImGuiRendering::PreRender(IDirect3DDevice9* device)
{
	ImGui_ImplDX9_NewFrame();
	_drawData.Valid = false;
	_drawList->Clear();
	_drawList->PushClipRectFullScreen();
}

void __stdcall ImGuiRendering::PostRender(IDirect3DDevice9* deivce)
{
	if (!_drawList->VtxBuffer.empty()) {
		_drawData.Valid = true;
		_drawData.CmdLists = &_drawList;
		_drawData.CmdListsCount = 1;
		_drawData.TotalVtxCount = _drawList->VtxBuffer.Size;
		_drawData.TotalIdxCount = _drawList->IdxBuffer.Size;
	}

	ImGui_ImplDX9_RenderDrawLists(&_drawData);
	ImGui::Render();
}
void ImGuiRendering::DrawEspBox(Vector leftUpCorn, Vector rightDownCorn, Color clr, float width)
{
	ImVec2 min = ImVec2(leftUpCorn.x, leftUpCorn.y);
	ImVec2 max = ImVec2(rightDownCorn.x, rightDownCorn.y);
	_drawList->AddRect(min, max, clr.GetU32(), 0.0F, -1, width);
}