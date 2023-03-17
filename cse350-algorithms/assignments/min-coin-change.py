def min_coin_change(target: int, coins: list[int]) -> list[int]:
    sum_table = [0] + [target + 1 for _ in range(target)]
    zeros = [0 for _ in range(len(coins))]
    count_table = [zeros] + [zeros for _ in range(target)]

    for i in range(1, len(sum_table)):
        selected: int | None = None
        for j in range(len(coins)):
            if coins[j] <= i and sum_table[i - coins[j]] + 1 < sum_table[i]:
                sum_table[i] = sum_table[i - coins[j]] + 1
                selected = j
        if selected != None:
            count_table[i] = count_table[i - coins[selected]].copy()
            count_table[i][selected] = count_table[i - coins[selected]][selected] + 1

    return count_table[target]

def gcd(a: int, b: int) -> int:
    m = a % b
    while m != 0:
        a, b = b, m
        m = a % b
    return b

def gcd_all(nums: list[int]) -> int:
    res = gcd(nums[0], nums[1])
    for n in nums:
        res = gcd(res, n)
    return res

nums = list(map(int, input().split()))
coin_num = nums[0]
sep_idx = coin_num + 1
zero_idx = nums[sep_idx:].index(0)
coins = nums[1:sep_idx]
amounts = nums[sep_idx:sep_idx + zero_idx]

gcd_coins = gcd_all(coins)
for amount in amounts:
    gcd_coins_amount = gcd(gcd_coins, amount)
    opt_amount = amount // gcd_coins_amount
    opt_coins = list(map(lambda x: x // gcd_coins_amount, coins))

    res = min_coin_change(opt_amount, opt_coins)
    txts: list[str] = []
    for i in range(len(res)):
        txts.append('{}({})'.format(coins[i], res[i]))
    print('{}: {}'.format(amount, ' '.join(txts)))

