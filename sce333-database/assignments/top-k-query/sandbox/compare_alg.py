from collections import defaultdict

# D-dimensional sorted lists of pair(user_id, score)
def read_sorted_files(num_dim):
    list_sorted_entities = []
    uid2dim2value = defaultdict(dict)
    for dim in range(num_dim):
        sorted_entities = []
        with open("sorted_score_{}.txt".format(dim), "r", encoding="utf-8") as f:
            for line in f:
                words = line.strip().split("\t")
                if len(words) != 2:
                    continue
                uid = words[0]
                score = float(words[1])
                sorted_entities.append((uid,score))
                uid2dim2value[uid][dim] = score
        list_sorted_entities.append(sorted_entities)

    return list_sorted_entities, uid2dim2value


def compare_results(l1, l2):
    if len(l1) != len(l2):
        return False
    else:
        for i in range(len(l1)):
            if l1[i] != l2[i]:
                return False
        return True

# you can use print_head method to understand "list_sorted_entities" variable
def print_head(list_sorted_entities):
    print("shape of list_sorted_entities")
    for dim in range(len(list_sorted_entities)):
        print("Dim: {}".format(dim))
        line = "\t"
        for e in list_sorted_entities[dim][:3]:
            line += "{}, ".format(e)
        line += " ... "
        print(line)
    print("-----------------")



import topk as topk

def compare_algorithms(num_dim, top_k, list_sorted_entities_all, uid2dim2value):
    list_sorted_entities = list_sorted_entities_all[:num_dim]
    #print_head(list_sorted_entities)
    myTopk = topk.Algo(list_sorted_entities, uid2dim2value)

    uids_Naive, cnt_Naive = myTopk.Naive(num_dim, top_k)
    uids_Fagin, cnt_Fagin = myTopk.Fagin(num_dim, top_k)
    uids_TA, cnt_TA = myTopk.TA(num_dim, top_k)
    uids_NRA, cnt_NRA = myTopk.NRA(num_dim, top_k)

    print("Dim: {}, Top-K: {}".format(num_dim, top_k))
    if compare_results(uids_Naive, uids_Fagin) == False:
        print("!!Error in Fagin")
    if compare_results(uids_Naive, uids_TA) == False:
        print("!!Error in TA")
    if compare_results(uids_Naive, uids_NRA) == False:
        print("!!Error in NRA")

    print("\tNaive:\t{}".format(cnt_Naive))
    print("\tFagin:\t{}".format(cnt_Fagin))
    print("\tTA:\t{}".format(cnt_TA))
    print("\tNRA:\t{}".format(cnt_NRA))

if __name__ == "__main__":
    list_sorted_entities_all, uid2dim2value = read_sorted_files(3)
    compare_algorithms(3, 2, list_sorted_entities_all, uid2dim2value)
    compare_algorithms(3, 5, list_sorted_entities_all, uid2dim2value)
