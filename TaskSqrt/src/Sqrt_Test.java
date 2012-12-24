import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;




public class Sqrt_Test {
	@Test
	public void sqrttest(){
		double res = 2.0;
		assertTrue(res == Sqrt.sqrt(4.0));
	}
	@Test
	public void sqrttest2(){
		double res = 0.03162277660168379;
		assertTrue(res == Sqrt.sqrt(0.001));
	}
	@Test
	public void sqrttest3(){
		double res = 3.162277660168379E-11;
		assertTrue(res == Sqrt.sqrt(0.1e-20));
	}
	@Test
	public void sqrttest4(){
		double res = 1.0E10;
		assertTrue(res == Sqrt.sqrt(1.0e20));
	}
	@Test
	public void sqrttest5(){
		double res = 1.0E25;
		assertTrue(res == Sqrt.sqrt(1.0e50));
	}

}
