/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//Construction
BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}
//Deconstruction
BinaryTree::~BinaryTree()
{
	while (m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
	delete node;
	delete parent;

}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const
{
	return (m_pRoot == nullptr);
}

void BinaryTree::Insert(int a_nValue)
{
	//The current value is now the root of the tree.
	TreeNode* pCurrent = m_pRoot;
	//The new node will be the pointer value of the treenode.
	TreeNode* newNode = new TreeNode(a_nValue);

	//If theres nothing in the tree
	if (IsEmpty() == true)
	{
		m_pRoot = newNode; //The new node is now the root.
		return;
	}
	//If the current node is not null.
	while (pCurrent != nullptr)
	{
		//If the newNode's value is less than the current nodes data.
		if (newNode->GetData() < pCurrent->GetData())
		{
			//If the Current node has a left.
			if (!pCurrent->HasLeft())
			{
				break;
			}
			//Continues through the loop.
			pCurrent = pCurrent->GetLeft();
		}
		//If the newNode is larger than the current Nodes data.
		else if (newNode->GetData() > pCurrent->GetData())
		{
			//If the current node has a right.
			if (!pCurrent->HasRight())
			{
				break;
			}
			//Continues through the loop.
			pCurrent = pCurrent->GetRight();
		}
		//If the value of the new node is equal to the currentnodes data.
		else if (newNode->GetData() == pCurrent->GetData())
		{
			std::cout << "The number already exists" << std::endl;
			break;
		}
	}
	//if the newNode's data is less than the currentnodes data.
	if (newNode->GetData() < pCurrent->GetData())
	{
		//Set the left of the currentnode to the newNode.
		pCurrent->SetLeft(newNode);
	}

	else if (newNode->GetData() > pCurrent->GetData())
	{
		//The newnode will be on the right of the current node.
		pCurrent->SetRight(newNode);
	}

}

void BinaryTree::Insert(TreeNode* newNode)
{
	//The current value is now the root of the tree.
	TreeNode* pCurrent = m_pRoot;
	//The new node will be the pointer value of the treenode.
	

	//If theres nothing in the tree
	if (IsEmpty() == true)
	{
		m_pRoot = newNode; //The new node is now the root.
		return;
	}
	//If the current node is not null.
	while (pCurrent != nullptr)
	{
		//If the newNode's value is less than the current nodes data.
		if (newNode->GetData() < pCurrent->GetData())
		{
			//If the Current node has a left.
			if (!pCurrent->HasLeft())
			{
				break;
			}
			//Continues through the loop.
			pCurrent = pCurrent->GetLeft();
		}
		//If the newNode is larger than the current Nodes data.
		else if (newNode->GetData() > pCurrent->GetData())
		{
			//If the current node has a right.
			if (!pCurrent->HasRight())
			{
				break;
			}
			//Continues through the loop.
			pCurrent = pCurrent->GetRight();
		}
		//If the value of the new node is equal to the currentnodes data.
		else if (newNode->GetData() == pCurrent->GetData())
		{
			std::cout << "The number already exists" << std::endl;
			break;
		}
	}
	//if the newNode's data is less than the currentnodes data.
	if (newNode->GetData() < pCurrent->GetData())
	{
		//Set the left of the currentnode to the newNode.
		pCurrent->SetLeft(newNode);
	}

	else if (newNode->GetData() > pCurrent->GetData())
	{
		//The newnode will be on the right of the current node.
		pCurrent->SetRight(newNode);
	}

}

//Finds the value within the binary tree.
TreeNode* BinaryTree::Find(int a_nValue)
{
	node = nullptr;
	parent = m_pRoot;

	return FindNode(a_nValue, node, parent) ? node : nullptr;
}
//Finds the node with the value and the node's location with the parent.
bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	//Making the node equal the parents location.
	node = ppOutParent;
	parent = nullptr;//Parent is equal to nullptr
	while (node != nullptr)
	{
		if (a_nSearchValue == node->GetData())//Data is equal to the nodes data.
		{
			ppOutNode = node;//node out is equal to the node.
			ppOutParent = parent;//Parent is equal to the parameters parent.
			return true;//Returns the function as true that it is found.
		}
		else
		{
			if (a_nSearchValue < node->GetData())
			{
				parent = node;//Parent is set to the nodes value.
				if (node->HasLeft() == true)
				{
					node = node->GetLeft();//Node is set to the next left value of node.
				}
				else
					break;

			}
			else
			{
				parent = node;
				if (node->HasRight() == true)
				{
					node = node->GetRight();//Node is set to the next right value of node.
				}
				else
					break;

			}
		}

	}

	return false;
}
//removes the node.
void BinaryTree::Remove(int a_nValue)
{
	node = nullptr;
	parent = m_pRoot;
	//If the tree is empty
	if (IsEmpty() == true)
	{
		//If theres nothing within the project.
		std::cout << "Sorry, theres nothing within the list." << std::endl;
		return;
	}

	//Checks the program to see if the value with the node and parent exist.
	if (FindNode(a_nValue, node, parent) == true)
	{
		//This is holding the values of the left and right of the node.
		TreeNode* tempNodeLeft = node->GetLeft();
		TreeNode* tempNodeRight = node->GetRight();

		//If the parent does exist.
		if (parent != nullptr)
		{
			if (parent->GetLeft() == node)//If the left of the parent is the node
			{
				parent->SetLeft(nullptr);//It sets the left of the node to nullptr
			}
			if (parent->GetRight() == node)//If the right of the parent is the node
			{
				parent->SetRight(nullptr);//It sets the right of the node to nullptr
			}
		}
		if (node == m_pRoot)//If the parent doesnt exist and the node is the root
		{
			m_pRoot = nullptr;//The root will now be a nullptr
		}
		if (tempNodeLeft != nullptr)//if the temp node to the left does not equal to nullptr
		{
			Insert(tempNodeLeft);//It will activate the insert function

		}
		if (tempNodeRight != nullptr)//if the temp node to the right does not equal to nullptr
		{
			Insert(tempNodeRight);//It will activate the insert function
		}
	}
}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{

	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);

			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}