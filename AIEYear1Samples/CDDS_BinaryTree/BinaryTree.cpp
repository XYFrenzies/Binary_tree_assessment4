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


BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

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

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
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

TreeNode* BinaryTree::Find(int a_nValue)
{
	node = nullptr;
	parent = m_pRoot;

	return FindNode(a_nValue, node, parent) ? node : nullptr;
}

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
		if (!node->HasLeft() && !node->HasRight())
		{
			delete node;
			return;
		}

		else if (parent->GetLeft() == node)
		{
			parent->SetLeft(nullptr);
			if (!node->HasLeft() && !node->HasRight())
			{
				delete node;
				return;
			}
			
			TreeNode* tempNode = node->GetRight();
			TreeNode* tempofTempNode = node->GetRight();
			while (node->HasRight())
			{

				 if (tempNode->GetLeft() == nullptr)
				 {
					 break;
				 }
				 tempNode = tempNode->GetLeft();
			}
			//test, trying to get the low value to come all the way to the top
			//tempNode = node;
			tempNode->SetLeft(node->GetLeft());
			parent->SetLeft(tempNode);
			tempNode->SetRight(tempofTempNode);
			delete node;

		}
		//if the parent's deleted value is on the right.
		else if (parent->GetRight() == node)
		{
			//The link between the node and the parent becomes nullptr.
			parent->SetRight(nullptr);

			if (!node->HasLeft() && !node->HasRight())
			{
				delete node;
				return;
			}
			TreeNode* tempNode = node->GetRight();
			TreeNode* tempofTempNode = node->GetRight();
			while (node->HasRight())
			{
				if (tempNode->GetLeft() == nullptr)
				{
					break;
				}
				tempNode = tempNode->GetLeft();

			}
			//test, trying to get the low value to come all the way to the top
			//tempNode = node;
			tempNode->SetLeft(node->GetLeft());
			parent->SetRight(tempNode);
			tempNode->SetRight(tempofTempNode);
			delete node;
		}
	}

}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
	PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

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