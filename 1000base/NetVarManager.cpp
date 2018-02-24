#include "Main.h"

CNetVars* g_pNetvars;

CNetVars::CNetVars()
{
	const ClientClass* clientClass = I::Client->GetAllClasses();

	while (clientClass != nullptr)
	{
		const auto classInfo = std::make_shared<Node>(0);
		RecvTable* recvTable = clientClass->rtTable;

		this->PopulateNodes(recvTable, &classInfo->nodes);
		nodes.emplace(recvTable->GetName(), classInfo);

		clientClass = clientClass->pNextClass;
	}
}

void CNetVars::PopulateNodes(RecvTable* recvTable, MapType* mapType)
{
	for (auto i = 0; i < recvTable->GetNumProps(); i++)
	{
		const RecvProp* prop = recvTable->GetProp(i);
		const auto  propInfo = std::make_shared<Node>(prop->GetOffset());

		if (prop->GetType() == SendPropType::DPT_DataTable)
			this->PopulateNodes(prop->GetDataTable(), &propInfo->nodes);

		mapType->emplace(prop->GetName(), propInfo);
	}
}