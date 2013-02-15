package clouds_tests;

import clouds.Daylights;
import clouds.IDaylight;

public class Daylight_test implements IDaylight{
    private Daylights mDaylight;
    
    public Daylight_test(Daylights daylight){
    	mDaylight = daylight;
    }
    
    @Override
    public Daylights Current() {
        return mDaylight;
    }
    
}