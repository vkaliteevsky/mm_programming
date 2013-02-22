/**
 * @author vkaliteevskiy
 * PartlyCloudy
 * (c)2012
 */

package clouds_tests;

import static org.junit.Assert.assertEquals;

import org.jmock.Expectations;
import org.jmock.Mockery;
import org.junit.Test;


import clouds.Clouds;
import clouds.Creature;
import clouds.Creatures;
import clouds.Daylights;
import clouds.IDaylight;
import clouds.ILuminary;
import clouds.IMagic;
import clouds.IWind;
import clouds.Magic;

public class Cloud_test {
    
    private Mockery context = new Mockery();
    final IDaylight dl = context.mock(IDaylight.class);
    final IWind w = context.mock(IWind.class);
    final ILuminary l = context.mock(ILuminary.class);
    final IMagic m = context.mock(IMagic.class);
    
    public Cloud_test() {
    }
    
    @Test
    public void PuppyStaticCreate()
    {
        System.out.println("create puppy\n");
        Clouds instance = new Clouds(new Daylight_test(Daylights.Morning), new Luminary_test(true),
                                   new Wind_test(1), new Magic());
        Creatures expResult = Creatures.Puppy;
        Creature result = instance.Create();
        assertEquals(expResult, result.GetCreature());
    }
   
    @Test
    public void PigletStaticCreate()
    {
        System.out.println("create piglet\n");
        Clouds instance = new Clouds(new Daylight_test(Daylights.Evening), new Luminary_test(true),
                                   new Wind_test(5), new Magic());
        Creatures expResult = Creatures.Piglet;
        Creature result = instance.Create();
        assertEquals(expResult, result.GetCreature());
    }
    @Test
    public void HedgehogDynamicCreateTest() 
    {    
        Clouds clouds = new Clouds(dl, l, w, m);
        context.checking(new Expectations() 
        {{
            one(l).IsShining(); will(returnValue(false));
        	one(dl).Current(); will(returnValue(Daylights.Evening));
            one(w).PowerWind(); will(returnValue(9));
            one(m).CallDaemon(Creatures.Hedgehog);
        }}
        );
        clouds.Create();
        context.assertIsSatisfied();   
    }
    @Test
    public void PuppyDynamicCreateTest() 
    {    
        Clouds clouds = new Clouds(dl, l, w, m);
        context.checking(new Expectations() 
        {{
            one(dl).Current();  will(returnValue(Daylights.Morning));
            one(w).PowerWind();  will(returnValue(2));
            one(l).IsShining(); will(returnValue(true));
            one(m).CallStork(Creatures.Puppy);
        }}
        );
        clouds.Create();
        context.assertIsSatisfied();   
    }
    
 }
