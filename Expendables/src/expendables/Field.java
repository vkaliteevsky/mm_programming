/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Observable;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class Field extends JFrame {
	
	Model model;
	Controller controller;
	JPanel pane = new JPanel();
	
	private void initComponents() throws IOException {



			setLayout(null);
		this.setIconImage(ImageIO.read(new File("icon.jpg")));
		this.setResizable(false);
		this.setSize(807, 650);


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

		
		this.setIconImage(ImageIO.read(new File("icon.jpg")));
		this.setResizable(false);
		setLayout(null);
		
		this.setLayout(null);

		ImagePanel pp = new ImagePanel();
		pp.setLayout(null);
		pp.setSize(800, 600);


		try {
			pp.setImage(ImageIO.read(new File("Field_fon.jpg")));
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		ImagePanel icon_panel = new ImagePanel();
		icon_panel.setLayout(null);
		icon_panel.setSize(39, 39);
		try {
			icon_panel.setImage(ImageIO.read(new File("icon__.jpg")));
		} catch (IOException e) {
			e.printStackTrace();
		}
		icon_panel.setSize(39, 39);
		icon_panel.setPreferredSize(new Dimension(39, 39));
		icon_panel.setOpaque(false);
		this.setPreferredSize(new Dimension(807, 650));
		field_panel = new MyJPanel(model, controller, pp);
		//field_panel.setBackground(Color.GRAY);
		field_panel.setSize(800, 600);
		field_panel.setPreferredSize(new Dimension(800, 600));
		//field_panel.add(pp);
		field_panel.setLayout(null);
		field_panel.setVisible(true);
		
		field_panel.paintComponent();
		

		getContentPane().add(field_panel);

		

		pp.setPreferredSize(new Dimension(800, 600));
				
		this.pack();
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
	private MyJPanel field_panel;
}
