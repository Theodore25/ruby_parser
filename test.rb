# frozen_string_literal: true

def sum(a, b)
  a + b
end

list = [0, 1, 2, 3, 5]

b = 1
x = b
i = 100
s = (b + i) / 2

if x != 1
  list[i] = (b + list[i]) / 2
else
  x = b + 5
end

while i != 0 do
  if x != 1
    list[i] = (b + list[i]) / 2
  else
    x = b + 5
    break
  end
end
