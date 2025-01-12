import Language.Haskell.TH (Lit(IntegerL))
import Control.Monad.RWS (MonadState(put))
-- maxim4 :: Int -> Int -> Int -> Int -> Int
-- maxim4 a b c d =
--     let max1 = if a > b then a else b
--         max2 = if c > d then c else d
--     in if max1 > max2 then max1 else max2

-- main :: IO ()
-- main = do
--     putStrLn "a"
--     a <- getLine
--     putStrLn "b"
--     b <- getLine
--     putStrLn "c"
--     c <- getLine
--     putStrLn "d"
--     d <- getLine
--     let num1 = read a :: Int
--     let num2 = read b :: Int
--     let num3 = read c :: Int
--     let num4 = read d :: Int
--     let maxResult = maxim4 num1 num2 num3 num4
--     putStrLn ("Maxim " ++ show maxResult)

-- sumapatrate :: Int -> Int -> Int
-- sumapatrate a b = a * a + b * b
-- 3 4 10 9

-- main :: IO ()
-- main = do
--     putStrLn "a"
--     a <- getLine
--     putStrLn "b"
--     b <- getLine
--     let num1 = read a :: Int
--     let num2 = read b :: Int
--     let sumResult = sumapatrate num1 num2
--     putStrLn ("Suma patrate " ++ show sumResult)

factorial :: Integer -> Integer
factorial n  = if n == 0 then 1 else n * factorial (n - 1)
              

-- main :: IO ()
-- main = do
--     putStrLn "n"
--     n <- getLine
--     let num = read n :: Int
--     let fact = factorial num
--     putStrLn ("Factorial " ++ show fact)
functie :: Int -> String
functie n = if n `mod` 2 == 0 then "par" else "impar"

functie1 :: Int -> Int -> String
functie1 a b = if a>b then "Primul" else "Al doilea"

-- main :: IO ()
-- main = do
--     putStrLn "n"
--     n <- getLine
--     let num = read n :: Int
--     let result = functie num
--     putStrLn ("Numarul este " ++ result)

-- main :: IO ()
-- main = do
--     putStrLn "a="
--     a <- getLine
--     putStrLn "b="
--     b <- getLine
--     let n1 = read a :: Int
--     let n2 = read b :: Int
--     let result = functie1 n1 n2
--     putStrLn ("Numarul este " ++ result)

-- maxLista :: [Int] -> Int
-- maxLista [] = error "Lista vida"
-- maxLista [x] = x
-- maxLista (x:xs) = if x > maxLista xs then x else maxLista xs

-- main :: IO ()
-- main = do
--     putStrLn "Introduceti lista"
--     lista <- getLine
--     let listaInt = read lista :: [Int]
--     let result = maxLista listaInt
--     putStrLn ("Maximul din lista este " ++ show result)


poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a * x^2 + b * x + c


fizzbuzz :: Integer -> String
fizzbuzz n
    | n `mod` 15 == 0 = "FizzBuzz"
    | n `mod` 3 == 0 = "Fizz"
    | n `mod` 5 == 0 = "Buzz"


fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2     = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)

fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n = fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)

tribonacci :: Integer -> Integer
tribonacci 1 = 1
tribonacci 2 = 1
tribonacci 3 = 2
tribonacci n = tribonacci (n - 1) + tribonacci (n - 2) + tribonacci (n - 3)

binomial :: Integer -> Integer -> Integer
binomial n 0 = 1
binomial 0 k = 0
binomial n k = binomial (n - 1) (k - 1) + binomial (n - 1) k





main :: IO ()
main = do
    putStrLn "n="
    a <- getLine
    -- putStrLn "k="
    -- b <- getLine
    let x = read a :: Integer
    -- let y = read b :: Integer
    -- let result = binomial x y
    let fact = factorial x
    putStrLn ("Factorialul este " ++ show fact)
    -- putStrLn ("Binomial este " ++ show result)