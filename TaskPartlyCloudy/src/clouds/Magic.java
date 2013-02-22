/**
 * @author vkaliteevskiy
 * PartlyCloudy
 * (c)2012
 */

package clouds;

public class Magic implements IMagic {
	@Override
	public void CallDaemon(Creatures creature) {
		System.out.print("CallDaemon\n");
	}

	@Override
	public void CallStork(Creatures creature) {
		System.out.print("CallStork\n");
	}
}
