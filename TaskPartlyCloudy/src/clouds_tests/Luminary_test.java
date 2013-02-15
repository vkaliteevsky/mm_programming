package clouds_tests;

import clouds.ILuminary;

public class Luminary_test implements ILuminary {
	private boolean mLuminary;

	public Luminary_test(boolean luminary) {
		mLuminary = luminary;
	}

	@Override
	public boolean IsShining() {
		return mLuminary;
	}

}