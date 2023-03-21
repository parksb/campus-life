'''
1. Replace folder name "202312345" with your student !!
   !!WARNING!! you will get 0 score,
   if your folder name is "202312345"
2. Implement Fagin method
3. Implement TA method
4. Implement NRA method

Input: num_dim, top_k
    num_dim: Number of dimension
    top_k: Variable k in top-'k' query
Output: uids_result, cnt_access
    uid_result: Result of top-k uids of the scores.
                The summation function is used
                for the score function.

                i.e., num_dim = 4, k = 2
                ----------------------------
                 uid    D0   D1    D2    D3
                ----------------------------
                "001"    1    1     1     1
                "002"    2    2     2     2
                "003"    3    3     3     3
                "004"    5    5     5     5
                ----------------------------

                score("001") = 1 + 1 + 1 + 1 = 4
                score("002") = 2 + 2 + 2 + 2 = 8
                score("003") = 3 + 3 + 3 + 3 = 12  --> top-2
                score("004") = 4 + 4 + 4 + 4 = 16  --> top-1

                uids_result: ["004", "003"]

    cnt_access: Number of access in each algorithm

Tip: Use Naive method to check your code
     Naive method is the free gift for the code understanding
'''
from collections import defaultdict
from typing import Tuple

def get_score(list_values) -> float:
    result = 0.0
    for v in list_values:
        result += v
    return result

class Algo():
    def __init__(self, list_sorted_entities, uid2dim2value):
        self.list_sorted_entities = list_sorted_entities

        '''
        variable for random access,
        but please do not use this variable directly.
        If you want to get the value of the entity,
        use method 'random_access(uid, dim)'
        '''
        self.__uid2dim2value__ = uid2dim2value

    def random_access(cls, uid, dim) -> float:
        return cls.__uid2dim2value__[uid][dim]

    def find_empty_dim(cls, uid: str, num_dim: int, uid2dim2value: dict[str, dict[int, float]]):
        result = []
        for dim in range(num_dim):
            if dim not in uid2dim2value[uid]:
                result.append(dim)
        return result

    def Naive(cls, num_dim, top_k) -> Tuple[list, int]:
        uids_result = []
        cnt_access = 0

        # read all values from the sorted lists
        uid2dim2value = defaultdict(dict)
        for dim in range(num_dim):
            for uid, value in cls.list_sorted_entities[dim]:
                uid2dim2value[uid][dim] = value
                cnt_access += 1

        # compute the score and sort it
        uid2score = defaultdict(float)
        for uid, dim2value in uid2dim2value.items():
            list_values = []
            for dim in range(num_dim):
                list_values.append(dim2value[dim])
            score = get_score(list_values)
            uid2score[uid] = score

        sorted_uid2score = sorted(uid2score.items(), key = lambda x : -x[1])

        # get the top-k results
        for i in range(top_k):
            uids_result.append(sorted_uid2score[i][0])

        return uids_result, cnt_access

    # Please use random_access(uid, dim) for random access
    def Fagin(cls, num_dim, top_k) -> Tuple[list, int]:
        uids_result = []
        cnt_access = 0

        uid2dim2value: defaultdict[str, dict[int, float]] = defaultdict(dict)

        cnt_found = 0
        uid2empty_dim: defaultdict[str, list[int]] = defaultdict(list[int])
        for rank in range(len(cls.list_sorted_entities[0])):
            for dim in range(num_dim):
                uid, value = cls.list_sorted_entities[dim][rank]
                uid2dim2value[uid][dim] = value
                cnt_access += 1

                uid2empty_dim[uid] = cls.find_empty_dim(uid, num_dim, uid2dim2value)
                if not len(uid2empty_dim[uid]):
                    cnt_found += 1
            if cnt_found >= top_k:
                break

        uid2score: defaultdict[str, float] = defaultdict(float)
        for uid in uid2dim2value.keys():
            score = sum(uid2dim2value[uid].values())
            for dim in uid2empty_dim[uid]:
                score += cls.random_access(uid, dim)
            uid2score[uid] = score

        uids_result = list(map(lambda x: x[0], sorted(uid2score.items(), key=lambda x: -x[1])))[:top_k]

        return uids_result, cnt_access

    # Please use random_access(uid, dim) for random access
    def TA(cls, num_dim, top_k) -> Tuple[list, int]:
        cnt_access = 0

        uid2dim2value: defaultdict[str, dict[int, float]] = defaultdict(dict)
        top_k_uid2score: list[tuple[str, float]] = []

        for rank in range(len(cls.list_sorted_entities[0])):
            threshold = 0
            uids_to_find: set[str] = set()
            uid2empty_dim: defaultdict[str, list[int]] = defaultdict(list[int])

            for dim in range(num_dim):
                uid, value = cls.list_sorted_entities[dim][rank]
                uid2dim2value[uid][dim] = value
                threshold += value
                cnt_access += 1

                uid2empty_dim[uid] = cls.find_empty_dim(uid, num_dim, uid2dim2value)
                if len(uid2empty_dim[uid]):
                    uids_to_find.add(uid)

            uid2score: list[tuple[str, float]] = []
            for uid in uids_to_find:
                score = sum(uid2dim2value[uid].values())
                for dim in uid2empty_dim[uid]:
                    value = cls.random_access(uid, dim)
                    uid2dim2value[uid][dim] = value
                    score += value
                uid2score.append((uid, score))

            top_k_uid2score = sorted(top_k_uid2score + uid2score, key=lambda x: -x[1])[:top_k]
            if all(map(lambda x: x[1] >= threshold, top_k_uid2score)):
                break

        uids_result = list(map(lambda x: x[0], top_k_uid2score))
        return uids_result, cnt_access

    # You cannot use random access in this method
    def NRA(cls, num_dim, top_k) -> Tuple[list, int]:
        uids_result = []
        cnt_access = 0

        return uids_result, cnt_access
