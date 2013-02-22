/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.ScrollPane;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.List;
import java.util.Observable;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

public class LoadGame extends JFrame {
	JPanel pane = new JPanel();
	private static ArrayList<JButton> buttons = new ArrayList();
	Controller controller;
	Model model;

	public void paneVisibleTrue() {
		pane.setVisible(true);
	}

	private void initComponents() throws IOException {

		final JPanel labPanel = new JPanel();
		final JScrollPane scrollPane = new JScrollPane(labPanel);
		labPanel.setLayout(new BoxLayout(labPanel, BoxLayout.Y_AXIS));

		String list[] = new File("saves.").list();
		int length = list.length;
		String[] s = new String[length];

		for (int i = 0; i < length; i++) {
			// File save = new File
			// ("saves/"+"save"+String.valueOf(i+1)+".txt");
			RandomAccessFile save = new RandomAccessFile("saves/" + "save"
					+ String.valueOf(i + 1) + ".txt", "rw");
			s[i] = save.readLine();
		}
		// for (int i = 0; i < length; i++){
		for (int i = 1; i < 2; i++) {
			JButton button = new JButton(String.valueOf(i) + s[i]);
			button.setFont(new java.awt.Font("Tahoma", 1, 15));
			button.setOpaque(true);
			button.setContentAreaFilled(true);
			button.setBackground(Color.GRAY);
			String k3 = button.getText();

			// int k = i+1;

			// s[i] = save.readLine();
			// System.out.print("s[i] = " + s[i]);
			// this.setLocationRelativeTo(null);

			// String l2 = this.toString();
			// System.out.print("k3 = " + k3);
			String l = "";
			char c = k3.charAt(0);
			l = String.valueOf(c);
			// System.out.print("l = " + l);

			RandomAccessFile save = null;

			try {
				// save = new
				// RandomAccessFile("saves/"+"save"+String.valueOf(k)+".txt",
				// "rw");
				// System.out.print("lol");
				save = new RandomAccessFile("saves/" + "save" + l + ".txt",
						"rw");
			} catch (FileNotFoundException ex) {
				Logger.getLogger(LoadGame.class.getName()).log(Level.SEVERE,
						null, ex);
			}

			ArrayList<Unit> list1 = new ArrayList();
			ArrayList<Unit> list2 = new ArrayList();
			String str = "";
			int h;
			int x;
			int y;

			try {
				str = save.readLine();
				System.out.print(" str = " + str);

				str = save.readLine();

			} catch (IOException ex) {
				Logger.getLogger(LoadGame.class.getName()).log(Level.SEVERE,
						null, ex);
			}
			// String str20 = "";
			while (!("next".equals(str))) {

				try {

					// if ("next".equals(str))
					System.out.print("\nstrS = " + str);
					String str2 = save.readLine();
					//
					System.out.print("\nstrH = " + str2);
					h = Integer.valueOf(str2);
					String str3 = save.readLine();
					//
					System.out.print("\nstrX = " + str3);
					x = Integer.valueOf(str3);
					String str4 = save.readLine();
					//
					System.out.print("\nstrY = " + str4);
					y = Integer.valueOf(str4);
					if ("Swordsman".equals(str)) {
						// list1.add((new Swordsman(h,x,y)));
					} else if ("Pikeman".equals(str)) {
						// list1.add((new Pikeman(h,x,y)));
					} else if ("Archer".equals(str)) {
						// list1.add((new Archer(h,x,y)));
					} else if ("Knight".equals(str)) {
						// list1.add((new Knight(h,x,y)));
					} else {

					}
					str = save.readLine();
				} catch (IOException ex) {
					Logger.getLogger(LoadGame.class.getName()).log(
							Level.SEVERE, null, ex);
				}
			}
			System.out.print("lol111");
			while (!"end".equals(str)) {
				System.out.print("lol2");
				try {
					str = save.readLine();
					str = save.readLine(); // h =
											// Integer.valueOf(save.readLine());
					str = save.readLine(); // x =
											// Integer.valueOf(save.readLine());
					str = save.readLine(); // y =
											// Integer.valueOf(save.readLine());
					if ("Swordsman".equals(str)) {
						// list2.add((new Swordsman(h,x,y)));
					} else if ("Pikeman".equals(str)) {
						// list2.add((new Pikeman(h,x,y)));
					} else if ("Archer".equals(str)) {
						// list2.add((new Archer(h,x,y)));
					} else {
						// list2.add((new Knight(h,x,y)));
					}
				} catch (IOException ex) {
					Logger.getLogger(LoadGame.class.getName()).log(
							Level.SEVERE, null, ex);
				}
			}

			model = new Model();
			model.player1.army = list1;
			model.player2.army = list2;
			controller = new Controller(model);

			button.addMouseListener(new MouseAdapter() {
				@Override
				public void mouseClicked(MouseEvent evt) {
					/*
					 * setVisible(false); Field f = null;
					 * 
					 * 
					 * try { f = new Field(controller, model); } catch
					 * (IOException ex) {
					 * Logger.getLogger(ForsesOverview.class.getName
					 * ()).log(Level.SEVERE, null, ex); } f.setVisible(true);
					 */

				}
			});
			buttons.add(button);
			button.setAlignmentX(JLabel.CENTER_ALIGNMENT);
			labPanel.add(button);
			scrollPane.revalidate();
		}

		this.setIconImage(ImageIO.read(new File("icon.jpg")));
		this.setResizable(false);
		this.setSize(456, 309);
		this.setBackground(Color.GRAY);

		ImagePanel pp = new ImagePanel();
		try {
			pp.setImage(ImageIO.read(new File("Expendables_name.jpg")));
		} catch (IOException e) {
			e.printStackTrace();
		}

		pane.setBackground(Color.GRAY);
		pane.setSize(456, 309);
		pane.setOpaque(false);

		// pane.add(goldValue);

		// pp.add(pane, java.awt.BorderLayout.CENTER);
		pp.setBackground(Color.GRAY);
		pp.setPreferredSize(new Dimension(456, 309));

		pane.setVisible(true);
		this.add(pp, java.awt.BorderLayout.CENTER);

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(pp);
		pp.setLayout(layout);
		layout.setHorizontalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addGroup(
				layout.createSequentialGroup()
						.addGap(42, 42, 42)
						.addComponent(scrollPane,
								javax.swing.GroupLayout.PREFERRED_SIZE, 365,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addContainerGap(49, Short.MAX_VALUE)));
		layout.setVerticalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addGroup(
				javax.swing.GroupLayout.Alignment.TRAILING,
				layout.createSequentialGroup()
						.addContainerGap(85, Short.MAX_VALUE)
						.addComponent(scrollPane,
								javax.swing.GroupLayout.PREFERRED_SIZE, 175,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(49, 49, 49)));

		this.pack();
		this.setLocationRelativeTo(null);

	}

	private Controller getController() {
		return controller;
	}

	public LoadGame() throws IOException {
		super("Expendables. Load Game");
		initComponents();
	}

	ScrollPane scrollPane1;
}
