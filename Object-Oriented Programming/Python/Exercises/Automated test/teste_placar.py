import unittest as ut
from Placar import Placar

class TestePlacar(ut.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.pl2 = Placar()
    
    @classmethod
    def tearDownClass(cls):
        cls.pl2 = None

    def setUp(self):
        self.pl = Placar()
        for i in range(6):
            # deixa o 6 fixo para cobrir o caso em que pelo menos um dos valores eh diferente
            self.pl.add(i+1, [i+1, i+1, i+1, i+1, 6])
        self.pl.add(7, [2, 2, 3, 3, 3])
        self.pl.add(8, [1, 2, 3, 4, 5])
        self.pl.add(9, [1, 1, 1, 1, 5])
        self.pl.add(10, [1, 1, 1, 1, 1])

    def tearDown(self):
        self.pl = None
        
    def testAddInvalidPos(self):
        self.assertRaises(IndexError, self.pl.add, 0, [1, 1, 1, 1, 1])
        self.assertRaises(IndexError, self.pl.add, 11, [1, 1, 1, 1, 1])
    
    def testAddOccupiedPos(self):
        for i in range(6):
            self.assertRaises(ValueError, self.pl.add, i+1, [i+1, 2, 3, 4, 5])
        self.assertRaises(ValueError, self.pl.add, 7, [1, 1, 4, 4, 4])
        self.assertRaises(ValueError, self.pl.add, 8, [2, 3, 4, 5, 6])
        self.assertRaises(ValueError, self.pl.add, 9, [3, 3, 3, 3, 4])
        self.assertRaises(ValueError, self.pl.add, 10, [5, 5, 5, 5, 5])

    def testEmptyGetScore(self):
        self.assertEqual(TestePlacar().pl2.getScore(), 0)

    def testGetScoreAtPos(self):
        for i in range(5):
            self.assertEqual(self.pl.getScore(i), (i+1)*4) 
        self.assertEqual(self.pl.getScore(5), 30)
        self.assertEqual(self.pl.getScore(6), 15)
        self.assertEqual(self.pl.getScore(7), 20)
        self.assertEqual(self.pl.getScore(8), 30)
        self.assertEqual(self.pl.getScore(9), 40)

    def testFullGetScore(self):
        self.assertEqual(self.pl.getScore(), 195)

    def testNoneGetTaken(self):
        for i in range(10):
            self.assertEqual(TestePlacar().pl2.getTaken(i), False)

    def testAllGetTaken(self):
        for i in range(10):
            self.assertEqual(self.pl.getTaken(i), True)


    def testGetName(self):    
        for i in range(10):
            self.assertEqual(self.pl.getName(i), Placar().nomes[i])

    def testFullHand(self):
        hand1 = [1, 1, 2, 2, 2]
        hand2 = [1, 1, 1, 2, 2]
        self.assertEqual(self.pl.checkFull(hand1), True)
        self.assertEqual(self.pl.checkFull(hand2), True)

    def testSequence(self):
        hand1 = [1, 2, 3, 4, 5]
        hand2 = [2, 3, 4, 5, 6]
        self.assertEqual(self.pl.checkSeqMaior(hand1), True)
        self.assertEqual(self.pl.checkSeqMaior(hand2), True)

    def testFourOfKind(self):
        hand1 = [1, 1, 1, 1, 2]
        hand2 = [1, 2, 2, 2, 2]
        self.assertEqual(self.pl.checkQuadra(hand1), True)
        self.assertEqual(self.pl.checkQuadra(hand2), True)

    def testFiveOfKind(self):
        hand1 = [1, 1, 1, 1, 1]
        self.assertEqual(self.pl.checkQuina(hand1), True)

    def testEmptyBoard(self):
        toString = TestePlacar().pl2
        string = str(toString)

        expectedString = "(1)    |   (7)    |  (4) \n\
-------|----------|-------\n\
(2)    |   (8)    |  (5) \n\
-------|----------|-------\n\
(3)    |   (9)    |  (6) \n\
-------|----------|-------\n\
       |   (10)   |\n\
       +----------+\n"
    
        self.assertEqual(expectedString, string)

    def testNotEmptyBoard(self):
        toString = self.pl
        string = str(toString)
        
        expectedString = " 4     |    15    |   16 \n\
-------|----------|-------\n\
 8     |    20    |   20 \n\
-------|----------|-------\n\
 12    |    30    |   30 \n\
-------|----------|-------\n\
       |    40    |\n\
       +----------+\n"
    
        self.assertEqual(expectedString, string)

if __name__ == '__main__':
    ut.main()