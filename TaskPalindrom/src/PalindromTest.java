import static org.junit.Assert.*;

import org.junit.Test;



public class PalindromTest {

	@Test
	public void test1() throws Exception {
		String s = "joj";
		Sensitive str = new Sensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test2() throws Exception {
		String s = "Joj";
		Sensitive str = new Sensitive();
		str.isPalindrom(s);
		assertFalse(str.isPalindrom(s));
	}
	@Test
	public void test3() throws Exception {
		String s = "";
		Sensitive str = new Sensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test4() throws Exception {
		String s = "";
		Insensitive str = new Insensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test5() throws Exception {
		String s = "G";
		Sensitive str = new Sensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test6() throws Exception {
		String s = "G";
		Insensitive str = new Insensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test7() throws Exception {
		String s = "d";
		Sensitive str = new Sensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test8() throws Exception {
		String s = "f";
		Insensitive str = new Insensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test9() throws Exception {
		String s = "fffffff";
		Insensitive str = new Insensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test10() throws Exception {
		String s = "ffff    fff";
		Insensitive str = new Insensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test11() throws Exception {
		String s = " j .. . . J";
		Insensitive str = new Insensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test12() throws Exception {
		String s = "jJ";
		Insensitive str = new Insensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
	@Test
	public void test13() throws Exception {
		String s = "JJ";
		Sensitive str = new Sensitive();
		str.isPalindrom(s);
		assertTrue(str.isPalindrom(s));
	}
}
