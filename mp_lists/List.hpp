/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include <iostream>
#include "List.h"

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* node = head_;
  while (head_ != NULL) {
    node = head_->next;
    delete head_;
    head_ = node;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
 	ListNode * newNode = new ListNode(ndata);
  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
    length_ = 1;
    return;
  }
  head_->prev = newNode;
  newNode->prev = NULL;
  newNode -> next = head_;
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  newNode->next = NULL;
  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
    length_ = 1;
    return;
  }
  tail_->next = newNode;
  newNode->prev = tail_;
  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (splitPoint >= length_) {
    return NULL;
  }
  if (splitPoint < 0) {
    return NULL;
  }
  if (splitPoint == 0) {
    return head_;
  }
  ListNode * curr = start;
  for (int i = 0; i < splitPoint; i++) {
    curr = curr->next;
  }
  curr->prev->next = NULL;
  curr->prev = NULL;
  tail_ = curr->prev;
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if (length_ < 3) {
    return;
  }
  ListNode* curr = head_;
  ListNode* curr_past1;
  ListNode* curr_past2;
  ListNode* curr_past3;
  ListNode* curr_next;
  int count = 0;
  while (count < length_) {
    if ((count + 1) % 3 == 0) {
      if (count == 2) {
        curr_past1 = curr->prev;
        curr_past2 = curr_past1->prev;
        curr_next = curr->next;
        curr_past2->prev = curr;
        curr->next = curr_past2;
        curr_past2->next = curr_next;
        curr_next->prev = curr_past2;
        curr_past1->prev = NULL;
        head_ = curr_past1;
        curr = curr_past2;
      } else {
        curr_past1 = curr->prev;
        curr_past2 = curr_past1->prev;
        curr_past3 = curr_past2->prev;
        if (curr->next != NULL) {
          curr_next = curr->next;
          curr_past1->prev = curr_past3;
          curr_past3->next = curr_past1;
          curr_past2->prev = curr;
          curr->next = curr_past2;
          curr_past2->next = curr_next;
          curr_next->prev = curr_past2;
          curr = curr_past2;
        } else {
          curr_past1->prev = curr_past3;
          curr_past3->next = curr_past1;
          curr_past2->prev = curr;
          curr->next = curr_past2;
          curr_past2->next = NULL;
          tail_ = curr_past2;
          curr = curr_past2;
        }
      }
    }
    curr = curr->next;
    count++;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) {
    return;
  }
  ListNode* curr = startPoint;
  ListNode* curr_prev = startPoint->prev;
  ListNode* curr_next = startPoint->next;
  while (curr != endPoint) {
    if (curr == startPoint) {
      curr_next = curr->next;
      curr->next = endPoint->next;
      curr->prev = curr_next;
      curr = curr_next;
    } else {
      curr_next = curr->next;
      curr->next = curr->prev;
      curr->prev = curr_next;
      curr = curr_next;
    }
  }
  endPoint->next = endPoint->prev;
  endPoint->prev = curr_prev;
  
  if (head_ == startPoint) {
    head_ = endPoint;
  } else {
    curr_prev->next = endPoint;
    endPoint->prev = curr_prev;
  }

  if (tail_ == endPoint) {
    tail_ = startPoint;
  } else {
    startPoint->next->prev = startPoint;
    startPoint->prev->next = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n > length_) {
    reverse(head_, tail_);
    return;
  }
  ListNode* curr = head_;
  ListNode* curr_end = curr;
  int index = 0;
  while (curr != NULL) {
    while (index + 1 < n) {
      if (curr_end != tail_) {
        curr_end = curr_end->next;
      }
      index++;
    }
    reverse(curr, curr_end);
    curr = curr->next;
    curr_end = curr;
    index = 0;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL && second == NULL) {
    return NULL;
  }
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  ListNode* merged;
  ListNode* curr;
	if (first->data < second->data) {
		merged = first;
    merged->prev = NULL;
		first = first->next;
	} else {
		merged = second;
    merged->prev = NULL;
		second = second->next;
	}
	curr = merged;
	while (first != NULL && second != NULL) {
		if (second->data < first->data) {
			second->prev = curr;
      curr->next = second;
      curr = curr->next;
			second = second->next;
		}
		else {
			first->prev = curr;
      curr->next = first;
      curr = curr->next;
			first = first->next;
		}
	}
	if (first == NULL) {
		second->prev = curr;
    curr->next = second;
	} else if (second == NULL) {
		first->prev = curr;
    curr->next = first;
	}
	return merged;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start == NULL) {
    return NULL;
  }
  if (start->next == NULL) {
    return start;
  }
  if (chainLength == 0 || chainLength == 1) {
    return start;
  }
  int first_half = chainLength / 2;
  int second_half = chainLength - first_half;
  ListNode* mid = split(start, first_half);
  return merge(mergesort(start, first_half), mergesort(mid, second_half));
}
