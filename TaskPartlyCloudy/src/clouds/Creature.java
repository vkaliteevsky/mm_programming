package clouds;

public class Creature {
    private Creatures mCreature;
    
    public Creature(Creatures creature){
        mCreature = creature;
    }
    
    public Creatures GetCreature(){
        return mCreature;
    }
}