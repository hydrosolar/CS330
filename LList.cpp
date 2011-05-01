/*
 *  LList.cpp
 *  Game
 *
 *  Created by Andrew Peddicord on 2/17/11.
 *  Copyright 2011 Capital University. All rights reserved.
 *
 */

#include "LList.h"
#include "LListIterator.h"
#include <iostream>
//------------------------------------------------------------
LList::LList() {
	this->size_ = 0;
	this->head_ = NULL;
	this->tail_ = NULL;
}
//------------------------------------------------------------
LList::~LList() {
    ListNode *node = this->head_;
	ListNode *temp;
	int i;
	for (i=0; i<this->size_; ++i) {
		temp = node->next_;
		delete[] node;
		node = temp;
	}
}
//------------------------------------------------------------

LList::LList(const LList& source) {
    this->size_ = 0;
    this->head_ = NULL;
    this->tail_ = NULL;
	LListIterator it;
	it.init(source);
	Drawable* item;
	while ((item = it.next())) {
		this->append(item);
	}
}

//------------------------------------------------------------
Drawable* LList::removeFirst() {
	ListNode *node;
	Drawable *item = NULL;
	if (this->size_ > 0) {
		item = this->head_->item_;
		if (this->size_ > 1) {
			node = this->head_;
			this->head_ = this->head_->next_;
			delete node;
		} else {
			delete this->head_;
			this->head_ = NULL;
			this->tail_ = NULL;
		}
		this->size_--;
	}
	return item;
}
//------------------------------------------------------------
void LList::append(Drawable *item){
	ListNode *temp = new ListNode();
	temp->item_ = item;
	
	if (this->size_ == 0) {
		this->head_ = temp;
		this->tail_ = temp;
	} else {
		this->tail_->next_ = temp;
        this->tail_ = temp;
	}
	this->size_++;
}
//------------------------------------------------------------
Drawable* LList::first() const {
    if (this->head_) {
        return this->head_->item_;
    }
    return NULL;
}
//------------------------------------------------------------
void LList::removeDrawable(Drawable *obj) {
	int i;
	ListNode *prenode;
	ListNode *node = this->head_;
    //Find the object
	for (i = 0; i<(this->size_); i++) {
		if (node->item_ == obj) {
			break;
		}
		prenode = node;
		node = node->next_;
	}
    //If it is the first
	if (i == 0) {
		removeFirst();
		return;
    //If it is the last
	} else if (i == ((this->size_) - 1)) {
		delete this->tail_;
		this->tail_ = prenode;
		this->tail_->next_ = NULL;
		this->size_--;
	} else if (i != (this->size_)) {
		prenode->next_ = node->next_;
		delete node;
		this->size_--;
	}
}
//------------------------------------------------------------
LList& LList::operator=(const LList &list) {
    this->size_ = 0;
    this->head_ = NULL;
    this->tail_ = NULL;
	LListIterator it;
	it.init(list);
	Drawable* item;
	while ((item = it.next())) {
		this->append(item);
	}
    return *this;
}
//------------------------------------------------------------
void LList::insertInSortedOrder(Drawable *item) {
    ListNode *node = this->head_;
    ListNode *temp = NULL;
    ListNode *newNode = new ListNode();
    newNode->item_ = item;
    int x, i;
    //Find a node with the left greator than the inserted item
    for (i = 0; i < (this->size_); ++i) {
        x = node->item_->left();
        if (item->left() <= x) {
            break;
        }
        temp = node;
        node = node->next_;
    }
    //If item is at the head
    if (i == 0){
        this->head_ = newNode;
        if (this->size() == 0) {
            this->tail_ = newNode;
        } else {
            newNode->next_ = node;
        }
        this->size_++;
    }
    //If it did not find a node
    else if (!node) {
        this->append(item);
    } else {
        temp->next_ = newNode;
        newNode->next_ = node;
        this->size_++;
    }
}