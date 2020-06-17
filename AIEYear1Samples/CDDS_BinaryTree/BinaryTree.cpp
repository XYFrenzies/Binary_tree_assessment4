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

	TreeNode* pCurrent = m_pRoot;
	//TreeNode* pParent = nullptr;
	TreeNode* newNode = new TreeNode(a_nValue);


	if (IsEmpty() == true)
	{
		m_pRoot = newNode;
		return;
	}
	while (pCurrent != nullptr)
	{

		if (newNode->GetData() < pCurrent->GetData())
		{
			if (!pCurrent->HasLeft())
			{
				break;
			}
			pCurrent = pCurrent->GetLeft();
		}
		else if (newNode->GetData() > pCurrent->GetData())
		{
			if (!pCurrent->HasRight())
			{
				break;
			}
			pCurrent = pCurrent->GetRight();
		}
		else if (newNode->GetData() == pCurrent->GetData())
		{
			std::cout << "The number already exists" << std::endl;
			break;
		}
	}
	if (newNode->GetData() < pCurrent->GetData())
	{
		pCurrent->SetLeft(newNode);
	}

	else
	{
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
					FindNode(a_nSearchValue, ppOutNode, ppOutParent);
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
					FindNode(a_nSearchValue, ppOutNode, ppOutParent);
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