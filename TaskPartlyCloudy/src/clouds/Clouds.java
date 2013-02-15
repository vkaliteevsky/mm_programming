package clouds;


	public class Clouds {
		private IDaylight mDaylight;
		private ILuminary mLuminary;
		private IWind mWind;
		private IMagic mMagic;


		public Clouds(IDaylight daylight, ILuminary luminary, IWind wind, IMagic magic){ 
	        mDaylight = daylight;
	        mLuminary = luminary;
	        mWind = wind;
	        mMagic = magic;
	      }

	    public Creature internalCreate() {
	    	boolean luminary = mLuminary.IsShining();
	    	Daylights daylight = mDaylight.Current();
	        int wind = mWind.PowerWind();
	        
	        if (luminary){

	              if (wind <= 3) {
	            	  if (daylight == Daylights.Morning) {
	                      return new Creature(Creatures.Puppy);
	            	  } else if (daylight == Daylights.Noon) {
	            		  return new Creature(Creatures.Baloon);
	            	  } else if (daylight == Daylights.Evening) {
	            		  return new Creature(Creatures.Bearcub);
	            	  } else {
	            		  return new Creature(Creatures.Bat);
	            	  }
	              } else if (wind >= 4 && wind <= 6) {
	            	  if (daylight == Daylights.Morning) {
	                      return new Creature(Creatures.Baloon);
	            	  } else if (daylight == Daylights.Noon) {
	            		  return new Creature(Creatures.Hedgehog);
	            	  } else if (daylight == Daylights.Evening) {
	            		  return new Creature(Creatures.Piglet);
	            	  } else {
	            		  return new Creature(Creatures.Puppy);
	            	  }
	              } else {
	            	  if (daylight == Daylights.Morning) {
	                      return new Creature(Creatures.Baloon);
	            	  } else if (daylight == Daylights.Noon) {
	            		  return new Creature(Creatures.Bearcub);
	            	  } else if (daylight == Daylights.Evening) {
	            		  return new Creature(Creatures.Puppy);
	            	  } else {
	            		  return new Creature(Creatures.Kitten);
	            	  }
	              }
	          } else {
	        	  if (wind <= 3) {
	            	  if (daylight == Daylights.Morning) {
	                      return new Creature(Creatures.Kitten);
	            	  } else if (daylight == Daylights.Noon) {
	            		  return new Creature(Creatures.Hedgehog);
	            	  } else if (daylight == Daylights.Evening) {
	            		  return new Creature(Creatures.Piglet);
	            	  } else {
	            		  return new Creature(Creatures.Puppy);
	            	  }
	              } else if (wind >= 4 && wind <= 6) {
	            	  if (daylight == Daylights.Morning) {
	                      return new Creature(Creatures.Baloon);
	            	  } else if (daylight == Daylights.Noon) {
	            		  return new Creature(Creatures.Bearcub);
	            	  } else if (daylight == Daylights.Evening) {
	            		  return new Creature(Creatures.Bat);
	            	  } else {
	            		  return new Creature(Creatures.Kitten);
	            	  }
	              } else {
	            	  if (daylight == Daylights.Morning) {
	                      return new Creature(Creatures.Hedgehog);
	            	  } else if (daylight == Daylights.Noon) {
	            		  return new Creature(Creatures.Bat);
	            	  } else if (daylight == Daylights.Evening) {
	            		  return new Creature(Creatures.Hedgehog);
	            	  } else {
	            		  return new Creature(Creatures.Puppy);
	            	  }
	              }
	          }
	    }

	 

	    public Creature Create()
	    {
	      Creature creature = internalCreate();
	      	switch (creature.GetCreature()) {
		          case Kitten: 
		              mMagic.CallStork(creature.GetCreature());  
		              break;
		          case Puppy:   
		              mMagic.CallStork(creature.GetCreature());  
		              break;
		          case Piglet:     
		              mMagic.CallStork(creature.GetCreature());  
		              break;
		          case Bearcub:  	        	  
		              mMagic.CallStork(creature.GetCreature());  
		              break;
		          case Hedgehog:
		              mMagic.CallDaemon(creature.GetCreature());  
		              break;  
		          case Bat:      
		              mMagic.CallDaemon(creature.GetCreature());  
		              break;  
		          case Baloon:                    
		              mMagic.CallDaemon(creature.GetCreature());  
		              break;                
	      	}       
	      return creature;
	    }
	}