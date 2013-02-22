/**
 * @author vkaliteevskiy
 * PartlyCloudy
 * (c)2012
 */

package clouds;

import java.util.Random;

public class Wind implements IWind{

    
    @Override
    public int PowerWind(){
        Random random = new Random();        
        int r = random.nextInt() % 10;
        return r;
    }
}