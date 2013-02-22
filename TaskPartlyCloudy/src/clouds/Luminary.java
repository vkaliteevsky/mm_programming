/**
 * @author vkaliteevskiy
 * PartlyCloudy
 * (c)2012
 */

package clouds;

import java.util.Random;

public class Luminary implements ILuminary{

   
    @Override
    public boolean IsShining(){
        Random random = new Random();
    	return random.nextBoolean();
    }
}
