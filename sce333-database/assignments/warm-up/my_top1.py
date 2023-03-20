'''
1. Replace folder name "202212345" with your student !!
   !!WARNING!! you will get 0 score,
   if your folder name is "202212345"
2. Implement
      get_score
   and
      get_top1_uid
'''


def get_score(list_values) -> float:
   result = 0

   '''
   get_score([1.2, 1.1, 1.0]) = 3.3
   result is the summation of all items of list_values
   '''
   for value in list_values:
      result += value

   return result

def get_top1_uid(uid2values) -> str | None:
   top1_uid = None

   '''
   implement your code here
   return the top-1 score uid
   e.g.,
   ------------------------------
   uid        0       1        2
   ------------------------------
   id_0000   1.2     1.1      1.0
   id_0001   3.6     3.6      3.7
   id_0002   4.8     6.2      5.2
   id_0003   2.2     2.3      1.9
   ------------------------------

   score "id_0000" = get_score([1.2, 1.1, 1.0]) = 3.3
   score "id_0001" = 10.9
   score "id_0002" = 16.2
   score "id_0003" = 6.4
   ...

   top1_uid = "id_0002"
   '''

   top1_score = None

   # in every uid, compute the score
   for uid, values in uid2values.items():
      score = get_score(values)
      if top1_score is None or score > top1_score:
         top1_score = score
         top1_uid = uid

   return top1_uid
