/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package anodizationscheduling;

/**
 *
 * @author edsa01
 */
public class Main {

    /**
     * @param args the command line arguments
     */
     
    public static void main(String[] args) {
        Anodizationprocess a1= new Anodizationprocess(1);
		Anodizationprocess a2= new Anodizationprocess(2);
		Anodizationprocess a3= new Anodizationprocess(3);
		Anodizationprocess a4= new Anodizationprocess(4);
		
		a1.steps.add(new Step(2,40));
		a1.steps.add(new Step(5,10));
		a1.steps.add(new Step(35,25));
		a2.steps.add(new Step(3,20));
		a2.steps.add(new Step(5,10));
		a2.steps.add(new Step(35,40));
    	a3.steps.add(new Step(2,10));
		a3.steps.add(new Step(5,5));
		a3.steps.add(new Step(3,12));
		a3.steps.add(new Step(5,5));
		a3.steps.add(new Step(4,5));
		a3.steps.add(new Step(5,5));
		a3.steps.add(new Step(7,1));
		a3.steps.add(new Step(8,5));
		a3.steps.add(new Step(9,10));
		a3.steps.add(new Step(35,30));
		a4.steps.add(new Step(2,10));
		a4.steps.add(new Step(5,5));
		a4.steps.add(new Step(3,12));
		a4.steps.add(new Step(5,5));
		a4.steps.add(new Step(7,8));
		a4.steps.add(new Step(8,5));
		a4.steps.add(new Step(9,5));
		a4.steps.add(new Step(16,56));
		a4.steps.add(new Step(18,5));
		a4.steps.add(new Step(30,5));
		a4.steps.add(new Step(35,30));
		
		//Calculate TMAX
        int tmax = 0;
        for (Step s : Step.steps) {
            tmax += s.duration;
        }
        System.out.println("param tmax := " + tmax + ";");
        System.out.println("");
        
        //Build Tank Set
        String tanks = "";
        for (Tank t : Tank.instances) {
            tanks = tanks + ("\"T" + t.number + "\",");
        }
        tanks = tanks.substring(0, tanks.length() - 1);
        System.out.println("set T " + tanks + ";");
        System.out.println("");

        //Build use_tank and duration params
        System.out.println("param : S :	use_tank\tduration\tts\ttl:=");
        for (Anodizationprocess p : Anodizationprocess.processes) {
            char iter = 'a';
            for (Step s : p.steps) {
                s.ts = Step.getPrevLowerBound(p, s);
                s.tl = Step.getUpperBound(tmax, p, s);

                String stepName = "an" + p.processNumber + (iter++);
                System.out.println("\t"+stepName+ "\t" + s.tank + "\t" + s.duration+"\t"+s.ts+"\t"+s.tl);
            }
        }
        System.out.println(";");
        System.out.println("");

        //Build followers
        System.out.println("param follows");
        for (Anodizationprocess p : Anodizationprocess.processes) {
            for (int stepIdx = 0; stepIdx < p.steps.size()-1; stepIdx++) {
                String step1Name = "an" + p.processNumber + (char)('a'+stepIdx);
                String step2Name = "an" + p.processNumber + (char)('a'+stepIdx+1);
                System.out.print("\t["+step1Name+","+step2Name+"]\t1");
            }
            System.out.println("");
        }

        System.out.println(";");
        System.out.println("");
    
    }
   
}
