#pragma once

class CNetVars
{
	struct Node;
	using MapType = std::unordered_map<std::string, std::shared_ptr<Node>>;

	struct Node
	{
		Node(int offset) : offset(offset) {}
		MapType nodes;
		int offset;
	};

	MapType nodes;

public:
	CNetVars();

private:
	void PopulateNodes(class RecvTable *recv_table, MapType *map);
	static int GetOffsetRecursive(MapType &map, int acc, const char *name)
	{
		return acc + map[name]->offset;
	}
	template<typename ...args_t>
	int GetOffsetRecursive(MapType &map, int acc, const char *name, args_t ...args)
	{
		const auto &node = map[name];
		return this->GetOffsetRecursive(node->nodes, acc + node->offset, args...);
	}

public:
	template<typename ...args_t>
	int GetOffset(const char *name, args_t ...args)
	{
		const auto &node = nodes[name];
		return this->GetOffsetRecursive(node->nodes, node->offset, args...);
	}
}; extern CNetVars* g_pNetvars;