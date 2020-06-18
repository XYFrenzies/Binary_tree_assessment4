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
	while(m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
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
	
	else
	{
		//The newnode will be on the right of the current node.
		pCurrent->SetRight(newNode);
	}
	
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = m_pRoot;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	TreeNode* pCurrent = ppOutParent;
	TreeNode* pParent = nullptr;
	while (pCurrent != nullptr)
	{
		if (a_nSearchValue == pCurrent->GetData())
		{
			ppOutNode = pCurrent;
			ppOutParent = pParent;
			return true;
		}
		else
		{
			if (a_nSearchValue < pCurrent->GetData())
			{
				pParent = pCurrent;
				if (pCurrent->HasLeft() == true)
				{
					pCurrent = pCurrent->GetLeft();
				}
				else
					break;

			}
			else
			{
				pParent = pCurrent;
				if (pCurrent->HasRight() == true)
				{
					pCurrent = pCurrent->GetRight();
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