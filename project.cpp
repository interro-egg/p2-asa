#include <iostream>
#include <string>
#include <vector>

typedef struct node {
	bool visited1 = false; // check
	bool visited2 = false; // search node's ancestors
	int parent1 = -1;	   // index
	int parent2 = -1;
} node;

bool build_tree(std::vector<node> &tree, int EDGE_NUMBER)
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
	if (count != EDGE_NUMBER)
		return false; // needed to pass the professors' tests

	return true;
}

//GIGA TODO: refactor everything
bool DFS_visit_and_check_tree_and_find_closest_common_ancestors(std::vector<node> &tree, int v, int v1, int v2, bool visit2, std::vector<int> &common_ancestors)
{
	if (v == v1 || v == v2) {
		// cenas
	} else {
		if (tree[v].visited1 == grey) {
			// found cycle! :) XD
			return false;
		}
		if (visit2 && tree[v].visited2) {
			// common ancestor
			common_ancestors.push_back(v);
			return true;
		}

		tree[v].visited1 = true;
		if (v == v1 || v == v2) {
			tree[v].visited2 = true;
		}

		if (tree[v].parent1 != -1 && !tree[tree[v].parent1].visited1) {
			if (!DFS_visit_and_check_tree_and_find_closest_common_ancestors(tree, tree[v].parent1)) {
				return false;
			}
		}
		if (tree[v].parent2 != -1 && !tree[tree[v].parent2].visited1) {
			if (!DFS_visit_and_check_tree_and_find_closest_common_ancestors(tree, tree[v].parent2)) {
				return false;
			}
		}
		// tree[v].visited1 = black;
	}
}

bool name_me(std::vector<node> &tree, int v1, int v2, std::vector<int> &common_ancestors, int EDGE_NUMBER)
{
	if (!build_tree(tree, EDGE_NUMBER))
		return false;

	for (size_t i = 1; i < tree.size(); i++)
		if (!tree[i].visited1)
			if (!DFS_visit_and_check_tree_and_find_closest_common_ancestors(tree, i, v1, v2, false, common_ancestors))
				return false;

	return true;
}

int main()
{
	int i;
	int v1, v2, TREE_SIZE, EDGE_NUMBER;
	std::cin >> v1 >> v2 >> TREE_SIZE >> EDGE_NUMBER;
	std::vector<node> tree(TREE_SIZE + 1); // 0 isn't used, it still works tho :sunglasses:
	std::vector<int> common_ancestors;
	if (name_me(tree, v1, v2, common_ancestors, EDGE_NUMBER)) {
		if (common_ancestors.size() == 0) {
			std::cout << "-" << std::endl;
		} else {
			for (int i : common_ancestors) {
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}
	} else {
		std::cout << "0" << std::endl;
	}
	return 0;
}