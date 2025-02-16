number = 0
g = 0

function randomize()
    math.randomseed(os.time())
    number = math.random(10)
end

function guess()
    print("Guess the number: ")
end

function check()
    if (g == number) then
        print("Correct!")
    elseif (g < number) then
        print("Too small!")
    elseif (g > number) then
        print("Too big!")
    end

    return g == number
end
