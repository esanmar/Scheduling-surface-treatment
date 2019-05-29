/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package anodizationscheduling;

import java.util.LinkedList;
import java.util.Vector;

/**
 *
 * @author edsa01
 */
public class Step {

    public final Tank tank;
    public final int duration;
    public static final Vector<Step> steps = new Vector<Step>();
    public int ts=1;
    public int tl=0;

    public Step(int tank, int duration) {
        this.tank = new Tank(tank);
        this.duration = duration;
        steps.add(this);
    }

    public static int getPrevLowerBound(Anodizationprocess p, Step ofStep){
        int val = 0;
        for(Step s : p.steps){
            if(s.equals(ofStep))
                break;
            val += s.duration;
        }
        return val;
    }

    public static int getUpperBound(int tmax, Anodizationprocess p, Step toStep){
        LinkedList<Step> revList = new LinkedList<Step>(p.steps);

        int val = tmax;
        while(revList.size() > 0){
            Step s = revList.removeLast();
            if(s.equals(toStep))
                break;
            val -= s.duration;
        }
        val-= toStep.duration;
        return val;
    }
}
