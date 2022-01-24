#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

enum color {
	white,
	grey,
	black,
};

typedef struct node {
	int bloodline = -1; // search node's ancestors
	int parent1 = -1;	// index
	int parent2 = -1;
	int color = white; // used for loop checking
} node;

bool build_tree(std::vector<node> &tree, int edge_number)
{
	int x, y, count = 0;
	while (std::cin >> x) {
		std::cin >> y;
		if (tree[y].parent1 == -1) {
			tree[y].parent1 = x;
		} else if (tree[y].parent2 == -1) {
			tree[y].parent2 = x;
		} else {
			return false;
		}
		count++;
	}
	if (count != edge_number)
		return false; // needed to pass the professors' tests

	return true;
}

bool DFS_Visit_Complete(std::vector<node> &tree, int i)
{
	if (tree[i].color == grey) {
		return false;
	}
	if (tree[i].color == white) {
		tree[i].color = grey;
		if (tree[i].parent1 != -1) {
			DFS_Visit_Complete(tree, tree[i].parent1);
		}
		if (tree[i].parent2 != -1) {
			DFS_Visit_Complete(tree, tree[i].parent2);
		}
		tree[i].color = black;
	}
	return true;
}

//checks for loops
bool DFS_Complete(std::vector<node> &tree, int tree_size)
{
	for (int i = 0; i < tree_size; i++) {
		if (tree[i].color == white) {
			if (!DFS_Visit_Complete(tree, i)) {
				return false;
			}
		}
	}
	return true;
}

void clear_ancestors(std::vector<node> &tree, int i, int v)
{
	tree[i].bloodline = v;
	if (tree[i].parent1 != -1) {
		clear_ancestors(tree, tree[i].parent1, v);
	}
	if (tree[i].parent2 != -1) {
		clear_ancestors(tree, tree[i].parent2, v);
	}
}

//TODO: Fix this function
void DFS_Bloodline(std::vector<node> &tree, int i, int v1, int v2, std::vector<int> &common_ancestors)
{

	if (tree[i].bloodline == v2) {
		common_ancestors.push_back(i);
		if (tree[i].parent1 != -1) {
			clear_ancestors(tree, tree[i].parent1, v1);
		}
		if (tree[i].parent2 != -1) {
			clear_ancestors(tree, tree[i].parent2, v1);
		}
	} else {
		tree[i].bloodline = v1;
		if (tree[i].parent1 != -1) {
			DFS_Bloodline(tree, tree[i].parent1, v1, v2, common_ancestors);
		}
		if (tree[i].parent2 != -1) {
			DFS_Bloodline(tree, tree[i].parent2, v1, v2, common_ancestors);
		}
	}
}

int main()
{
	int v1, v2, tree_size, edge_number;
	std::cin >> v1 >> v2 >> tree_size >> edge_number;
	std::vector<node> tree(tree_size + 1); // 0 isn't used, it still works tho :sunglasses:
	std::vector<int> common_ancestors;
	if (!build_tree(tree, edge_number) || !DFS_Complete(tree, tree_size)) {
		std::cout << "-" << std::endl;
		return 0;
	}
	DFS_Bloodline(tree, v1, v1, v2, common_ancestors);
	DFS_Bloodline(tree, v2, v2, v1, common_ancestors);
	sort(common_ancestors.begin(), common_ancestors.end());
	if (common_ancestors.size() == 0) {
		std::cout << "-" << std::endl;
	} else {
		for (size_t i = 0; i < common_ancestors.size(); i++) {
			std::cout << common_ancestors[i] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}