import collections
import random
import sys
from collections import deque

# Set recursion limit higher for recursive solutions like QuickSort/MergeSort
sys.setrecursionlimit(2000)

# ==============================================================================
# 1. Kth Largest/Smallest Element (without built-in sort)
#    Uses Quickselect, which leverages the partitioning logic of QuickSort for O(n) average time complexity.
# ==============================================================================

def partition(arr, low, high):
    """Lomuto partition scheme: partitions the array around a pivot."""
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def find_kth_largest(arr, k):
    """Finds the Kth largest element using Quickselect."""
    if not arr or k <= 0 or k > len(arr):
        return "Invalid input"

    # We are looking for the element at index (len(arr) - k) if the array were sorted.
    target_index = len(arr) - k
    
    # Work on a copy to avoid modifying the original list
    arr_copy = arr[:]
    low, high = 0, len(arr_copy) - 1

    while low <= high:
        pivot_index = partition(arr_copy, low, high)
        if pivot_index == target_index:
            return arr_copy[pivot_index]
        elif pivot_index < target_index:
            low = pivot_index + 1
        else:
            high = pivot_index - 1
    
    return "Error: Could not find Kth element."

def find_kth_smallest(arr, k):
    """Finds the Kth smallest element using Quickselect. Target index is k-1."""
    if not arr or k <= 0 or k > len(arr):
        return "Invalid input"

    # We are looking for the element at index (k - 1) if the array were sorted.
    target_index = k - 1
    
    arr_copy = arr[:]
    low, high = 0, len(arr_copy) - 1

    while low <= high:
        pivot_index = partition(arr_copy, low, high)
        if pivot_index == target_index:
            return arr_copy[pivot_index]
        elif pivot_index < target_index:
            low = pivot_index + 1
        else:
            high = pivot_index - 1
    
    return "Error: Could not find Kth element."


# ==============================================================================
# 2. Implement Merge Sort
# ==============================================================================

def merge_sort(arr):
    """Sorts an array using the Merge Sort algorithm (Divide and Conquer)."""
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left = arr[:mid]
    right = arr[mid:]

    left = merge_sort(left)
    right = merge_sort(right)

    return merge(left, right)

def merge(left, right):
    """Merges two sorted lists into a single sorted list."""
    result = []
    i = j = 0
    
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    # Append remaining elements
    result.extend(left[i:])
    result.extend(right[j:])
    
    return result

# ==============================================================================
# 3. Implement Quick Sort
# ==============================================================================

def quick_sort(arr, low, high):
    """Sorts an array using the Quick Sort algorithm (in-place modification)."""
    if low < high:
        # pi is partitioning index, arr[pi] is now at right place
        pi = partition(arr, low, high)
        
        # Recursively sort elements before and after partition
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)

# Note: This quick_sort uses the 'partition' function defined above for Kth element.

# ==============================================================================
# 4. Valid Palindrome Check (ignore special chars and spaces)
# ==============================================================================

def is_valid_palindrome(s):
    """Checks if a string is a palindrome, ignoring non-alphanumeric characters."""
    filtered_chars = []
    for char in s:
        if char.isalnum():
            filtered_chars.append(char.lower())
    
    # Join the filtered characters to form a clean string
    clean_s = "".join(filtered_chars)
    
    # Check if the cleaned string is equal to its reverse
    return clean_s == clean_s[::-1]

# ==============================================================================
# 5. Intersection and Union of Two Lists (without built-in set operations)
# ==============================================================================

def list_union(list1, list2):
    """Finds the union of two lists without using set operations."""
    # Start with a copy of list1
    union_list = list1[:]
    
    # Iterate through list2 and add elements not already in union_list
    for item in list2:
        if item not in union_list:
            union_list.append(item)
    return union_list

def list_intersection(list1, list2):
    """Finds the intersection of two lists without using set operations."""
    intersection_list = []
    
    # Use a frequency map (dictionary) for list1 to handle duplicates efficiently
    freq_map = collections.defaultdict(int)
    for item in list1:
        freq_map[item] += 1
        
    # Check list2 elements against the frequency map
    for item in list2:
        if freq_map[item] > 0:
            intersection_list.append(item)
            freq_map[item] -= 1 # Decrement count to handle duplicates properly
            
    return intersection_list

# ==============================================================================
# 6. Implement a Stack using Two Queues (and vice versa)
# ==============================================================================

class StackUsingTwoQueues:
    """Implements a Stack (LIFO) using two queues (FIFO)."""
    def __init__(self):
        self.q1 = deque() # Main queue for storing elements
        self.q2 = deque() # Helper queue

    def push(self, x):
        """Pushes element x onto the stack."""
        # Standard push: O(1)
        self.q1.append(x)

    def pop(self):
        """Removes the element on top of the stack and returns that element."""
        if not self.q1:
            return None # Stack is empty

        # Move n-1 elements from q1 to q2
        while len(self.q1) > 1:
            self.q2.append(self.q1.popleft())

        # Pop the last element (which is the stack's top element)
        top_element = self.q1.popleft()

        # Swap the names of q1 and q2 (q2 becomes the new main queue)
        self.q1, self.q2 = self.q2, self.q1
        
        return top_element

    def top(self):
        """Returns the element on top of the stack."""
        if not self.q1:
            return None

        # Similar process to pop, but push the element back to q2 before swap
        while len(self.q1) > 1:
            self.q2.append(self.q1.popleft())

        top_element = self.q1.popleft()
        self.q2.append(top_element) # Put it back

        self.q1, self.q2 = self.q2, self.q1
        return top_element
    
    def is_empty(self):
        return not self.q1

class QueueUsingTwoStacks:
    """Implements a Queue (FIFO) using two stacks (LIFO lists)."""
    def __init__(self):
        self.stack_in = []  # Stack for enqueuing (input)
        self.stack_out = [] # Stack for dequeuing (output)

    def push(self, x):
        """Pushes element x to the back of the queue (enqueue)."""
        # O(1) operation
        self.stack_in.append(x)

    def pop(self):
        """Removes the element from the front of the queue (dequeue)."""
        if not self.stack_out:
            # Transfer elements from stack_in to stack_out in reverse order
            while self.stack_in:
                self.stack_out.append(self.stack_in.pop())
        
        if self.stack_out:
            return self.stack_out.pop()
        else:
            return None # Queue is empty

    def peek(self):
        """Gets the front element."""
        if not self.stack_out:
            while self.stack_in:
                self.stack_out.append(self.stack_in.pop())

        if self.stack_out:
            return self.stack_out[-1]
        else:
            return None
    
    def is_empty(self):
        return not self.stack_in and not self.stack_out

# ==============================================================================
# 7. Write a Python program to reverse a linked list.
# ==============================================================================

class ListNode:
    """Node for a Singly Linked List."""
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def reverse_linked_list(head):
    """Reverses a singly linked list iteratively."""
    prev = None
    current = head
    while current:
        next_node = current.next # Store next node
        current.next = prev      # Reverse current node's pointer
        prev = current           # Move prev to current node
        current = next_node      # Move current to next node
    return prev # New head is the old tail (prev)

# Helper function to convert list to linked list
def list_to_linked_list(data):
    dummy = ListNode(0)
    tail = dummy
    for val in data:
        tail.next = ListNode(val)
        tail = tail.next
    return dummy.next

# Helper function to convert linked list to list for printing
def linked_list_to_list(head):
    data = []
    current = head
    while current:
        data.append(current.val)
        current = current.next
    return data

# ==============================================================================
# 8. Implement a binary search algorithm recursively.
# ==============================================================================

def binary_search_recursive(arr, target, low, high):
    """Recursively searches for a target in a sorted array."""
    if low > high:
        return -1 # Base case: target not found

    mid = (low + high) // 2
    
    if arr[mid] == target:
        return mid # Target found
    elif arr[mid] < target:
        # Search in the right half
        return binary_search_recursive(arr, target, mid + 1, high)
    else:
        # Search in the left half
        return binary_search_recursive(arr, target, low, mid - 1)

def find_binary_search(arr, target):
    """Wrapper function for recursive binary search."""
    # Ensure the array is sorted before calling binary search
    if arr != sorted(arr):
        print("Warning: Array should be sorted for binary search.")
        # Optionally, you could sort it here: arr.sort()
        
    return binary_search_recursive(arr, target, 0, len(arr) - 1)
  
