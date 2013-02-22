/**
 * @author vkaliteevskiy
 * PartlyCloudy
 * (c)2012
 */

package clouds;

import java.util.Random;

public class Daylight implements IDaylight {

	@Override
	public Daylights Current() {
		Random random = new Random();
		int i = random.nextInt() % 4;
		if (i == 0) {
			return Daylights.Morning;
		} else if (i == 1) {
			return Daylights.Noon;
		} else if (i == 2) {
			return Daylights.Evening;
		} else {
			return Daylights.Noon;
		}
	}
}