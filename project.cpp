#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

enum COLOR {
	WHITE, // not visited
	GREY,  // visiting
	BLACK, // visited
};

typedef struct node {
	int bloodline = -1; // search node's ancestors
	int parent1 = -1;	// index
	int parent2 = -1;
	int color = WHITE; // used for loop checking
	bool closest_common_ancestor = false;
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
	if (tree[i].color == GREY) {
		return false;
	}
	if (tree[i].color == WHITE) {
		tree[i].color = GREY;
		if (tree[i].parent1 != -1) {
			DFS_Visit_Complete(tree, tree[i].parent1);
		}
		if (tree[i].parent2 != -1) {
			DFS_Visit_Complete(tree, tree[i].parent2);
		}
		tree[i].color = BLACK;
	}
	return true;
}

// checks for loops
bool DFS_Complete(std::vector<node> &tree, int tree_size)
{
	for (int i = 0; i < tree_size; i++) {
		if (tree[i].color == WHITE) {
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
	tree[i].closest_common_ancestor = false;
	if (tree[i].parent1 != -1) {
		clear_ancestors(tree, tree[i].parent1, v);
	}
	if (tree[i].parent2 != -1) {
		clear_ancestors(tree, tree[i].parent2, v);
	}
}

// TODO: Fix this function
void DFS_Bloodline(std::vector<node> &tree, int i, int v1, int v2)
{

	if (tree[i].bloodline == v2) {
		tree[i].closest_common_ancestor = true;
		if (tree[i].parent1 != -1) {
			clear_ancestors(tree, tree[i].parent1, v1);
		}
		if (tree[i].parent2 != -1) {
			clear_ancestors(tree, tree[i].parent2, v1);
		}
	} else {
		tree[i].bloodline = v1;
		if (tree[i].parent1 != -1) {
			DFS_Bloodline(tree, tree[i].parent1, v1, v2);
		}
		if (tree[i].parent2 != -1) {
			DFS_Bloodline(tree, tree[i].parent2, v1, v2);
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	bool found = false;
	int v1, v2, tree_size, edge_number;
	std::cin >> v1 >> v2 >> tree_size >> edge_number;
	std::vector<node> tree(tree_size + 1); // 0 isn't used, it still works tho :sunglasses:
	std::vector<int> common_ancestors;
	if (!build_tree(tree, edge_number) || !DFS_Complete(tree, tree_size)) {
		std::cout << "-" << std::endl;
		return 0;
	}
	DFS_Bloodline(tree, v1, v1, v2);
	DFS_Bloodline(tree, v2, v2, v1);
	for (size_t i = 0; i < tree.size(); i++) {
		if (tree[i].closest_common_ancestor) {
			found = true;
			std::cout << i << " ";
		}
	}
	if (!found) {
		std::cout << "-" << std::endl;
	} else {
		std::cout << std::endl;
	}
	return 0;
}