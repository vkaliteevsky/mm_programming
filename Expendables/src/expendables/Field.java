/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.Color;
import java.awt.Graphics;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

public class Field extends JFrame {

	Model model;
	Controller controller;

	private void initComponents() throws IOException {

		Graphics g = this.getGraphics();

		this.setIconImage(ImageIO.read(new File("icon.jpg")));
		this.setResizable(false);
		this.setSize(800, 600);
		this.setBackground(Color.GRAY);
		jPanel1 = new MyJPanel();

		menu.add(file);
		file.setText("File");
		file.add(toMenu);
		setJMenuBar(menu);

		toMenu.setText("Menu");
		toMenu.addActionListener(new java.awt.event.ActionListener() {
			@Override
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				Expendables app = null;
				try {
					app = new Expendables(false, thisLink());
				} catch (IOException ex) {
					Logger.getLogger(Field.class.getName()).log(Level.SEVERE,
							null, ex);
				}
				app.setVisible(true);
			}
		});

		setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

		jPanel1.setBackground(new java.awt.Color(200, 200, 200));

		javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(
				jPanel1);
		jPanel1.setLayout(jPanel1Layout);
		jPanel1Layout.setHorizontalGroup(jPanel1Layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 800,
				Short.MAX_VALUE));
		jPanel1Layout.setVerticalGroup(jPanel1Layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 600,
				Short.MAX_VALUE));

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(
				getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addComponent(
				jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE,
				javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));
		layout.setVerticalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addComponent(
				jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE,
				javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

		jPanel1.paintComponents(g);

		pack();
		this.setLocationRelativeTo(null);
	}

	public Field(Controller c, Model m) throws IOException {
		model = m;
		controller = c;
		initComponents();
	}

	private Field thisLink() {
		return this;
	}

	private JMenuItem toMenu = new JMenuItem();
	private JMenuBar menu = new JMenuBar();
	private JMenu file = new JMenu();
	private javax.swing.JPanel jPanel1;
}
