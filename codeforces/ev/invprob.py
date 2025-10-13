from decimal import Decimal, getcontext

# Increase precision beyond default double
getcontext().prec = 50

n = int(input())
a = list(map(int, input().split()))

ans = Decimal(0)

for i in range(n):
    for j in range(i):
        if a[j] <= a[i]:
            k = a[j] * (a[j] - 1) // 2
        else:
            k = (a[i] * (a[i] - 1)) // 2 + (a[j] - a[i]) * a[i]
        ans += Decimal(k) / Decimal(a[j] * a[i])

# Output with 6 decimal places, rounding half to even
print(f"{ans:.6f}")

//