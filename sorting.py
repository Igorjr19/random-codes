#Bubble Sort
def bubble_sort(array):
  for i in range(0, len(array) - 1):
    for j in range(0, len(array) - i - 1):
      if(array[j] > array[j + 1]):
        aux = array[j]  
        array[j] = array[j + 1]
        array[j + 1] = aux

#Bubble Sort Melhorado
def bubble_sort_melhorado(array):
  troca = 1
  for j in range(0, len(array) - 1):
    if(troca):
      troca = 0
      for i in range(0, len(array) - j - 1):
        if(array[i] > array[i + 1]):
          troca = 1
          aux = array[i]
          array[i] = array[i + 1]
          array[i + 1] = aux

#Quick Sort - primeiro elemento como pivô
def particao_primeiro(array, first, last):
  pivot = array[first]
  up = last
  down = first + 1
  done = False

  while(not done):
    while(down <= up and array[down] <= pivot):
      down += 1
    while(up >= down and array[up] >= pivot):
      up -= 1
    if(up < down):
      done = True
    else:
      array[down], array[up] = array[up], array[down]

  array[up], array[first] = array[first], array[up]
  
  return up

def quick_sort_primeiro_aux(array, first, last):
  if(first < last):
    split = particao_primeiro(array, first, last)
    quick_sort_primeiro_aux(array, first, split - 1)
    quick_sort_primeiro_aux(array, split + 1, last)

def quick_sort_primeiro(array):
  quick_sort_primeiro_aux(array, 0, len(array) - 1)

#Quick Sort - elemento central como pivô
def particao_central(array, first, last):
  pivot = array[(first + last) // 2]
  up = last
  down = first
  done = False

  while(not done):
    while(down <= up and array[down] < pivot):
      down += 1
    while(up >= down and array[up] > pivot):
      up -= 1
    if(up < down):
      done = True
    else:
      array[down], array[up] = array[up], array[down]
      down += 1
      up -= 1
      
  return down


def quick_sort_central_aux(array, first, last):
  if(first < last):
    split = particao_central(array, first, last)
    if first < split - 1:
      quick_sort_central_aux(array, first, split - 1)
    if split < last:
      quick_sort_central_aux(array, split, last)

def quick_sort_central(array):
  quick_sort_central_aux(array, 0, len(array) - 1)

#Insertion Sort
def insertion_sort(array):
  for k in range(1, len(array)):
    y = array[k]
    j = k - 1

    while j >= 0 and array[j] > y:
      array[j + 1] = array[j]
      j -= 1
    array[j + 1] = y

#Shell Sort - Knuth gap
def shell_sort(array):
  gap_list = [1]
  while gap_list[len(gap_list) - 1] < len(array):
    gap_list.append(gap_list[len(gap_list) - 1] * 3 + 1)
  gap_list.reverse()

  for i in range(len(gap_list)):
    span = gap_list[i]
    for j in range(span, len(array)):
      y = array[j]
      k = j - span
      while k >= 0 and array[k] > y:
        array[k + span] = array[k]
        k -= span
      array[k + span] = y
      
#Selection Sort
def selection_sort(array):
  for i in range(len(array) - 1):
    menor = array[i]
    index = i
    for j in range(i + 1, len(array)):
      if array[j] < menor:
        menor = array[j]
        index = j
    array[index] = array[i]
    array[i] = menor

#Heap Sort
def build_max_heap(array, raiz, fundo):
  pronto = 0
  while raiz * 2 <= fundo and not pronto:
    if raiz * 2 == fundo:
      filhoMax = raiz * 2
    elif array[raiz * 2] > array[raiz * 2 + 1]:
      filhoMax = raiz * 2
    else:
      filhoMax = raiz * 2 + 1
    if array[raiz] < array[filhoMax]:
      array[raiz], array[filhoMax] = array[filhoMax], array[raiz]
      raiz = filhoMax
    else:
      pronto = 1

def heap_sort(array):
  i = len(array) // 2
  while i >= 0:
    build_max_heap(array, i, len(array) - 1)
    i -= 1
  i = len(array) - 1  
  while i >= 1:
    array[0], array[i] = array[i], array[0]
    build_max_heap(array, 0, i - 1)
    i -= 1

#Merge Sort
def merge(array, l, m, r):
  n1 = m - l + 1
  n2 = r - m

  L = [0] * n1
  R = [0] * n2

  for i in range(0, n1):
    L[i] = array[l + i]
  
  for j in range(0, n2):
    R[j] = array[m + j + 1]

  i = 0; j = 0; k = l

  while i < n1 and j < n2:
    if L[i] <= R[j]:
      array[k] = L[i]
      i += 1
    else: 
      array[k] = R[j]
      j += 1
    k += 1

  while i < n1:
    array[k] = L[i]
    i += 1
    k += 1
  while j < n2:
    array[k] = R[j]
    j += 1
    k += 1

def merge_sort_aux(array, l, r):
  if l < r:
    m = l + (r - l) // 2

    merge_sort_aux(array, l, m)
    merge_sort_aux(array, m + 1, r)
    merge(array, l, m, r)

def merge_sort(array):
  merge_sort_aux(array, 0, len(array) - 1)
