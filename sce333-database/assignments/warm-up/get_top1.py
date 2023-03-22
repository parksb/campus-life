import my_top1

def read_file():
    with open("uid_values.txt", "r", encoding="utf-8") as f:
        uid2values = dict()
        for line in f:
            line = line.strip()
            words = line.split()
            uid = words[0]
            values = []
            for w in words[1:]:
                values.append(float(w))
            uid2values[uid] = values
        return uid2values
        
if __name__ == "__main__":
    uid2values = read_file()
    top1_uid = my_top1.get_top1_uid(uid2values)

    answer_uid = "id_0973"

    assert answer_uid == top1_uid
