/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package anodizationscheduling;

import java.util.Vector;

/**
 *
 * @author edsa01
 */
public class Tank {
    public final static Vector<Tank> instances = new Vector<Tank>();

    public final int number;
    public Tank(int number){
        this.number = number;
        if(!instances.contains(this))
            instances.add(this);
    }

    @Override
    public String toString() {
        return "T"+number;
    }


    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Tank other = (Tank) obj;
        if (this.number != other.number) {
            return false;
        }
        return true;
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 47 * hash + this.number;
        return hash;
    }



}
