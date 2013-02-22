/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JPanel;

/**
 * 
 * @author vkalit-lenovo
 */
public class MyJPanel extends JPanel {
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		for (int i = 0; i <= 800; i += 40) {
			g.drawLine(i, 0, i, 600);
		}
		for (int j = 0; j <= 600; j += 40) {
			g.drawLine(0, j, 800, j);
		}		
	}

	

	protected void paintUnit(Graphics g, int x, int y){
		super.paintComponent(g);
		g.setColor(Color.GREEN);
		g.drawRect(x, y, 40, 40);
		
	}
}
