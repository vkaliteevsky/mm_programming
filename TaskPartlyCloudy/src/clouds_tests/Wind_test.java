package clouds_tests;

import clouds.IWind;

public class Wind_test implements IWind {
	private int mWind;

	public Wind_test(int wind) {
		mWind = wind;
	}

	@Override
	public int PowerWind() {
		return mWind;
	}

}