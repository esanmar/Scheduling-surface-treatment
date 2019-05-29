/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package anodizationscheduling;

import anodizationscheduling.*;
import java.util.Vector;

/**
 *
 * @author edsa01
 */
public class Anodizationprocess {
    public final static Vector<Anodizationprocess> processes = new Vector<Anodizationprocess>();
    public final Vector<Step> steps = new Vector<Step>();

    public final int processNumber;
    public Anodizationprocess(int processNumber){
        this.processNumber = processNumber;
        processes.add(this);
    }
}
