class Job:
    def __init__(self, start, finish, profit):
        self.start = start;
        self.finish = finish
        self.profit = profit


def binary_search(jobs, start):
    lo, hi = 0, start - 1
    while lo <= hi:
        mid = (lo + hi) // 2
        if jobs[mid].finish <= jobs[start].start:
            if jobs[mid + 1].finish <= jobs[start].start:
                lo = mid + 1
            else:
                return mid
        else:
            hi = mid - 1
    return -1

def schedule(jobs):

    jobs = sorted(jobs, key = lambda j : j.finish)
    n = len(jobs)
    table = [0 for _ in range(n)]
    table[0] = jobs[0].profit
    for i in range(1, n):
        profitInclJob = jobs[i].profit
        otherJobId = binary_search(jobs, i)
        if otherJobId != -1:
            profitInclJob += table[otherJobId]
        table[i] = max(profitInclJob, table[i - 1])
    return table[n - 1]


def main():
    job = [Job(1, 2, 50), Job(3, 5, 20), Job(6, 19, 100), Job(2, 100, 200)]
    print ("Optimal profit is: %d" % schedule(job))

if __name__ == '__main__':
    main()
