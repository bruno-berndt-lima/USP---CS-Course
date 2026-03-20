import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

 
class PlacarTest {
	private int i;
	private  Placar pl;

	@BeforeEach
	void setUp() throws Exception {
		pl = new Placar();
	}

	@AfterEach
	void tearDown() throws Exception {
		pl = null;
	}
	
	@Test
	void testEmptyGetScore() {
        assertEquals(pl.getScore(), 0);
	}
	
	@Test
	void testGetScore() {
		for(i = 1; i <= 6; i++) {
			pl.add(i, new int[] {i, i, i, i, 6});
		}
		pl.add(7, new int[] {2, 2, 3, 3, 3});
		pl.add(8, new int[] {1, 2, 3, 4, 5});
		pl.add(9, new int[] {1, 1, 1, 1, 2});
		pl.add(10, new int[] {1, 1, 1, 1, 1});
        assertEquals(pl.getScore(), 195);
	}
	
	@Test
	void testAddInvalidPos() {
		assertThrows(IllegalArgumentException.class, () -> pl.add(0, new int[] {1, 1, 1, 1, 1}));
		assertThrows(IllegalArgumentException.class, () -> pl.add(11, new int[] {1, 1, 1, 1, 1}));
	}
	
	@Test
	void testAddOccupiedPos() {
		for(i = 1; i <= 6; i++) {
			pl.add(i, new int[] {i, i, i, i, 6});
		}
		pl.add(7, new int[] {2, 2, 3, 3, 3});
		pl.add(8, new int[] {1, 2, 3, 4, 5});
		pl.add(9, new int[] {1, 1, 1, 1, 2});
		pl.add(10, new int[] {1, 1, 1, 1, 1});
		
		for(i = 1; i <= 6; i++) {
			assertThrows(IllegalArgumentException.class, () -> pl.add(i, new int[] {i, i, 3, 4, 5}));
		}
		assertThrows(IllegalArgumentException.class, () -> pl.add(7, new int[] {1, 1, 4, 4, 4}));
		assertThrows(IllegalArgumentException.class, () -> pl.add(8, new int[] {2, 3, 4, 5, 6}));
		assertThrows(IllegalArgumentException.class, () -> pl.add(9, new int[] {3, 3, 3, 3, 4}));
		assertThrows(IllegalArgumentException.class, () -> pl.add(10, new int[] {5, 5, 5, 5, 5}));
	}
	
	@Test
	void testAddWrongHand() {	
		// full, seq, quadra, quina
		pl.add(7, new int[] {1, 1, 1, 1, 2});
		pl.add(8, new int[] {1, 1, 1, 1, 2});
		pl.add(9, new int[] {1, 1, 1, 2, 2});
		pl.add(10, new int[] {1, 1, 1, 1, 2});
		
        assertEquals(pl.getScore(), 0);
	}	
	
	@Test
	void testFullHand() {
		pl.add(7, new int[] {1, 1, 1, 2, 2});
		pl = new Placar();
		pl.add(7, new int[] {1, 2, 2, 2, 2});
		pl = new Placar();
		pl.add(7, new int[] {1, 1, 2, 3, 3});
	}
	@Test
	void testQuadra() {
		// V V V | V V F | V F V | V F F | F V V | F V F | F F V | F F F
		
		pl.add(9, new int[] {1, 1, 1, 1, 2});
		pl = new Placar();
		pl.add(9, new int[] {1, 1, 1, 2, 2});
		pl = new Placar();		
		pl.add(9, new int[] {1, 1, 2, 2, 2});
		pl = new Placar();	
		pl.add(9, new int[] {1, 1, 2, 3, 3});
		pl = new Placar();
		pl.add(9, new int[] {1, 2, 2, 2, 3});
		pl = new Placar();
		pl.add(9, new int[] {1, 2, 2, 3, 3});
		pl = new Placar();
		pl.add(9, new int[] {1, 2, 3, 3, 3});
		pl = new Placar();
		pl.add(9, new int[] {1, 2, 3, 4, 4});
		pl = new Placar();
		
		pl.add(9, new int[] {1, 2, 2, 2, 2});
		pl = new Placar();
		pl.add(9, new int[] {1, 2, 2, 2, 3});
		pl = new Placar();		
		pl.add(9, new int[] {1, 2, 2, 3, 3});
		pl = new Placar();	
		pl.add(9, new int[] {1, 2, 2, 3, 4});
		pl = new Placar();
		pl.add(9, new int[] {1, 1, 2, 2, 2});
		pl = new Placar();
		pl.add(9, new int[] {1, 1, 2, 2, 3});
		pl = new Placar();
		pl.add(9, new int[] {1, 2, 3, 4, 4});
		pl = new Placar();
		pl.add(9, new int[] {1, 2, 3, 4, 5});
		pl = new Placar();

	}
	@Test
	void testQuina() {
		// V V V V | V V V F | V V F V | V F V V | F V V V | F F F V |
		// F F V F | F V F F | V F F F | F F F F | V V F F | F F V V |
		// V F F V | F V V F | V F V F | F V F V
		pl.add(10, new int[] {1, 1, 1, 1, 1});
		pl = new Placar();
		pl.add(10, new int[] {1, 1, 1, 1, 2});
		pl = new Placar();
		pl.add(10, new int[] {1, 1, 1, 2, 2});
		pl = new Placar();
		pl.add(10, new int[] {1, 1, 2, 2, 2});
		pl = new Placar();
		pl.add(10, new int[] {1, 2, 2, 2, 2});
		pl = new Placar();
		pl.add(10, new int[] {1, 2, 3, 4, 4});
		pl = new Placar();
		pl.add(10, new int[] {1, 2, 3, 3, 4});
		pl = new Placar();
		pl.add(10, new int[] {1, 2, 2, 3, 4});
		pl = new Placar();
		pl.add(10, new int[] {1, 1, 2, 3, 4});
		pl = new Placar();
		pl.add(10, new int[] {1, 2, 3, 4, 5});
		pl = new Placar();
		pl.add(10, new int[] {1, 1, 1, 2, 3});
		pl = new Placar();
		pl.add(10, new int[] {1, 2, 3, 3, 3});
		pl = new Placar();
		pl.add(10, new int[] {1, 1, 2, 3, 3});
		pl = new Placar();
		pl.add(10, new int[] {1, 2, 2, 2, 3});
		pl = new Placar();
		pl.add(10, new int[] {1, 1, 2, 2, 3});
		pl = new Placar();
		pl.add(10, new int[] {1, 2, 2, 3, 3});
		pl = new Placar();
	}
	@Test
	void testSeq() {
		// V V V V | V V V F | V V F V | V F V V | F V V V | F F F V |
		// F F V F | F V F F | V F F F | F F F F | V V F F | F F V V |
		// V F F V | F V V F | V F V F | F V F V
		pl.add(8, new int[] {1, 2, 3, 4, 5});
		pl = new Placar();
		pl.add(8, new int[] {1, 2, 3, 4, 4});
		pl = new Placar();
		pl.add(8, new int[] {1, 2, 3, 3, 4});
		pl = new Placar();
		pl.add(8, new int[] {1, 2, 2, 3, 4});
		pl = new Placar();
		pl.add(8, new int[] {1, 1, 2, 3, 4});
		pl = new Placar();
		pl.add(8, new int[] {1, 1, 1, 1, 2});
		pl = new Placar();
		pl.add(8, new int[] {1, 1, 1, 2, 2});
		pl = new Placar();
		pl.add(8, new int[] {1, 1, 2, 2, 2});
		pl = new Placar();
		pl.add(8, new int[] {1, 2, 2, 2, 2});
		pl = new Placar();
		pl.add(8, new int[] {1, 1, 1, 1, 1});
		pl = new Placar();
		pl.add(8, new int[] {1, 2, 3, 3, 3});
		pl = new Placar();
		pl.add(8, new int[] {1, 1, 1, 2, 3});
		pl = new Placar();
		pl.add(8, new int[] {1, 2, 2, 2, 3});
		pl = new Placar();
		pl.add(8, new int[] {1, 1, 2, 3, 3});
		pl = new Placar();
		pl.add(8, new int[] {1, 2, 2, 3, 3});
		pl = new Placar();
		pl.add(8, new int[] {1, 1, 2, 2, 3});
		pl = new Placar();
	}
	
	@Test
	void testToString() {
		for(i = 1; i <= 6; i++) {
			pl.add(i, new int[] {i, i, i, i, 6});
		}
		pl.add(7, new int[] {2, 2, 3, 3, 3});
		pl.add(8, new int[] {1, 2, 3, 4, 5});
		pl.add(9, new int[] {1, 1, 1, 1, 2});
		pl.add(10, new int[] {1, 1, 1, 1, 1});
		
		String expectedString = "4      |   15     |   16  \n" + 
				"--------------------------\n" + 
				"8      |   20     |   20  \n" + 
				"--------------------------\n" + 
				"12     |   30     |   30  \n" + 
				"--------------------------\n" + 
				"       |   40     |\n" + 
				"       +----------+\n";
		
		String string = pl.toString();
		
		assertEquals(expectedString, string);	
	}
	
	@Test
	void testToString2() {
		String expectedString = "(1)    |   (7)    |   (4) \n" + 
				"--------------------------\n" + 
				"(2)    |   (8)    |   (5) \n" + 
				"--------------------------\n" + 
				"(3)    |   (9)    |   (6) \n" + 
				"--------------------------\n" + 
				"       |   (10)   |\n" + 
				"       +----------+\n";
		
		String string = pl.toString();
		
		assertEquals(expectedString, string);	
	}

	
	
	
}
