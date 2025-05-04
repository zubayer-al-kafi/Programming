a, b = map(int, input().split())
apb = a ** b
bpa = b ** a
final_result = apb - bpa
print(final_result)