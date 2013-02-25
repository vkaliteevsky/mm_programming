/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.*;
import javax.swing.*;

public class ImagePanel extends JPanel {
	private Image image;

	public Image getImage() {
		return image;
	}

	public void setImage(Image image) {
		this.image = image;
	}

	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		//if (image != null) {
			g.drawImage(image, 0, 0, getWidth(), getHeight(), null);
		//}
	}
}