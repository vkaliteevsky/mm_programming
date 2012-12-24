

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Test;



public class Recognize_test {
	@Test
	public void testrecognize(){
		assertTrue(Recognize.recognize("()"));
	}
	@Test
	public void testrecognize1(){
		assertTrue(Recognize.recognize("([])"));
	}
	@Test
	public void testrecognize2(){
		assertFalse(Recognize.recognize("([)]"));
	}
	@Test
	public void testrecognize3(){
		assertFalse(Recognize.recognize("<name height = 13, weigth = 184 ][]> [()] </name> </name>"));
	}
	@Test
	public void testrecognize4(){
		assertTrue(Recognize.recognize("(<name> 123[([]())] Frodo </name>)[]"));
	}
	@Test
	public void testrecognize5(){
		assertFalse(Recognize.recognize("(<f></f><l2> l2 ... </l2> </name> hhm [its cool] "));
	}
	@Test
	public void testrecognize6(){
		assertTrue(Recognize.recognize("<f> </f>"));
	}
	@Test
	public void testrecognize7(){
		assertTrue(Recognize.recognize(""));
	}
}
