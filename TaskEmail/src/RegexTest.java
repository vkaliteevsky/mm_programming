import static org.junit.Assert.*;

import org.junit.Test;

	
public class RegexTest {


		@Test
		public void testcheck(){
			assertTrue(Regex.check("vkalit@gmail.com"));
		}
		@Test
		public void testcheck1(){
			assertTrue(Regex.check("a@b.cc"));
		}
		@Test
		public void testcheck2(){
			assertTrue(Regex.check("victor.polozov@mail.ru"));
		}
		@Test
		public void testcheck3(){
			assertTrue(Regex.check("my@domain.info"));
		}
		@Test
		public void testcheck4(){
			assertTrue(Regex.check("_.1@mail.com"));
		}
		@Test
		public void testcheck5(){
			assertTrue(Regex.check("coins@hermitage.museum"));
		}
		@Test
		public void testcheck6(){
			assertFalse(Regex.check("a@b.c"));
		}
		@Test
		public void testcheck7(){
			assertFalse(Regex.check("a..b@mail.ru"));
		}
		
		@Test
		public void testcheck8(){
			assertFalse(Regex.check(".a@mail.ru"));
		}
		
		@Test
		public void testcheck9(){
			assertFalse(Regex.check("yo@domain.domain"));
		}
		
		@Test
		public void testcheck10(){
			assertFalse(Regex.check("1@mail.ru"));
		}
		
		
		
		/*	@Test
		public void testinter_segment2(){
			assertFalse(Inter_segment.inter_segment(0,0,1,1,2,2,3,3));
		}
		@Test
		public void testinter_segment3(){
			assertTrue(Inter_segment.inter_segment(0,0,1,0,0,0,0,1));
		}
		@Test
		public void testinter_segment4(){
			assertTrue(Inter_segment.inter_segment(0,0,3,3,2,2,4,4));
		}
		@Test
		public void testinter_segment5(){
			assertFalse(Inter_segment.inter_segment(0,0,0,3,2,2,2,4));
		}
	*/
}
