/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.util.Observable;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class NewGame extends JFrame {// implements ActionListener{
	private MyField goldValue;
	private MyField swordsmanValue;
	private MyField pikemanValue;
	private MyField knightValue;
	private MyField archerValue;
	private Controller controller;
	private Model model = new Model();
	Initialization init;

	JPanel pane = new JPanel();

	public void paneVisibleTrue() {
		pane.setVisible(true);
	}

	private void initComponents() throws IOException {
		init = new Initialization(this);

		this.setIconImage(ImageIO.read(new File("icon.jpg")));
		this.setResizable(false);
		this.setSize(800, 600);
		this.setBackground(Color.GRAY);

		error = new MyJOptionPane() {
			@Override
			public void update(Observable o, Object arg) {
				if (((Model) o).isError())
					MyJOptionPane.showMessageDialog(this,
							"There's no modey to do there.");
			}

		};
		// MyJOptionPane.showMessageDialog(this, "There's no \"there\" there.");

		label1 = new MyLabel() {

			@Override
			public void update(Observable o, Object arg) {
				label1.setText("  " + ((Model) o).cur.name);
			}
		};
		label1.setFont(new java.awt.Font("Tahoma", 1, 25));
		jButton1 = new javax.swing.JButton();
		label2 = new MyLabel() {

			@Override
			public void update(Observable o, Object arg) {
				label2.setText("Gold: " + ((Model) o).cur.getGold());
			}
		};
		label2.setFont(new java.awt.Font("Tahoma", 1, 25));
		jButton2 = new javax.swing.JButton();
		jButton3 = new javax.swing.JButton();
		jButton4 = new javax.swing.JButton();
		jButton7 = new javax.swing.JButton();
		jTextField3 = new MyField() {

			@Override
			public void update(Observable o, Object arg) {
				jTextField3.setText("Swordsman: "
						+ ((Model) o).cur.getSwordsman());
			}
		};
		jTextField4 = new MyField() {

			@Override
			public void update(Observable o, Object arg) {
				jTextField4.setText("Pikeman: " + ((Model) o).cur.getPikeman());
			}
		};
		jTextField5 = new MyField() {

			@Override
			public void update(Observable o, Object arg) {
				jTextField5.setText("Archer: " + ((Model) o).cur.getArcher());
			}
		};
		jTextField6 = new MyField() {

			@Override
			public void update(Observable o, Object arg) {
				jTextField6.setText("Knight: " + ((Model) o).cur.getKnight());
			}
		};

		goldValue = new MyField() {
			@Override
			public void update(Observable o, Object o1) {
				setText(((Model) o).cur.getGold());
			}

		};
		controller = new Controller(model);
		model.addObserver(goldValue);
		model.addObserver(label1);
		model.addObserver(label2);
		model.addObserver(jTextField3);
		model.addObserver(jTextField4);
		model.addObserver(jTextField5);
		model.addObserver(jTextField6);
		model.addObserver(error);

		ImagePanel pp = new ImagePanel();
		try {
			pp.setImage(ImageIO.read(new File("Expendables_menu.jpg")));
		} catch (IOException e) {
			e.printStackTrace();
		}

		pane.setBackground(Color.GRAY);
		pane.setSize(800, 600);
		pane.setOpaque(false);

		// pane.add(goldValue);

		// pp.add(pane, java.awt.BorderLayout.CENTER);
		pp.setBackground(Color.GRAY);
		pp.setPreferredSize(new Dimension(800, 600));

		jButton1.setText("Swordsman 50");
		jButton1.setFont(new java.awt.Font("Tahoma", 1, 20));
		jButton1.setOpaque(true);
		jButton1.setContentAreaFilled(true);
		jButton1.setBackground(Color.GRAY);

		jButton2.setText("Pikeman 75");
		jButton2.setFont(new java.awt.Font("Tahoma", 1, 20));
		jButton2.setOpaque(true);
		jButton2.setContentAreaFilled(true);
		jButton2.setBackground(Color.GRAY);

		jButton3.setText("Archer 100");
		jButton3.setFont(new java.awt.Font("Tahoma", 1, 20));
		jButton3.setOpaque(true);
		jButton3.setContentAreaFilled(true);
		jButton3.setBackground(Color.GRAY);

		jButton4.setText("Knight 150");
		jButton4.setFont(new java.awt.Font("Tahoma", 1, 20));
		jButton4.setOpaque(true);
		jButton4.setContentAreaFilled(true);
		jButton4.setBackground(Color.GRAY);

		jButton7.setText("Next");
		jButton7.setFont(new java.awt.Font("Tahoma", 1, 25));
		jButton7.setOpaque(true);
		jButton7.setContentAreaFilled(true);
		jButton7.setBackground(Color.GRAY);

		javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(
				pane);
		pane.setLayout(jPanel1Layout);
		jPanel1Layout
				.setHorizontalGroup(jPanel1Layout
						.createParallelGroup(
								javax.swing.GroupLayout.Alignment.LEADING)
						.addGroup(
								javax.swing.GroupLayout.Alignment.TRAILING,
								jPanel1Layout
										.createSequentialGroup()
										.addContainerGap(44, Short.MAX_VALUE)
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.TRAILING,
																false)
														.addComponent(
																jTextField3)
														.addComponent(label2)
														.addComponent(
																label1,
																javax.swing.GroupLayout.Alignment.LEADING)
														.addComponent(
																jButton1,
																javax.swing.GroupLayout.Alignment.LEADING,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																185,
																Short.MAX_VALUE)
														.addComponent(
																jButton2,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jButton3,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jButton4,
																javax.swing.GroupLayout.Alignment.LEADING,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jButton7,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jTextField4,
																javax.swing.GroupLayout.Alignment.LEADING)
														.addComponent(
																jTextField5,
																javax.swing.GroupLayout.Alignment.LEADING)
														.addComponent(
																jTextField6,
																javax.swing.GroupLayout.Alignment.LEADING))
										.addGap(48, 48, 48)));
		jPanel1Layout
				.setVerticalGroup(jPanel1Layout
						.createParallelGroup(
								javax.swing.GroupLayout.Alignment.LEADING)
						.addGroup(
								jPanel1Layout
										.createSequentialGroup()
										.addGap(36, 36, 36)
										.addComponent(
												label1,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												33,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addGap(1, 1, 1)
										.addComponent(
												label2,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												30,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(
												jButton1,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												41,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(
												jButton2,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												41,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(
												jButton3,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												41,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(
												jButton4,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												41,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(
												jTextField3,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												28,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(
												jTextField4,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												28,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(
												jTextField5,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												28,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED,
												javax.swing.GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addComponent(
												jTextField6,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												28,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addGap(18, 18, 18)
										.addComponent(
												jButton7,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												41,
												javax.swing.GroupLayout.PREFERRED_SIZE)));

		javax.swing.GroupLayout Layout = new javax.swing.GroupLayout(pp);
		pp.setLayout(Layout);
		Layout.setHorizontalGroup(Layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addGroup(
				Layout.createSequentialGroup()
						.addGap(256, 256, 256)
						.addComponent(pane,
								javax.swing.GroupLayout.PREFERRED_SIZE,
								javax.swing.GroupLayout.DEFAULT_SIZE,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addContainerGap(267, Short.MAX_VALUE)));
		Layout.setVerticalGroup(Layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addGroup(
				Layout.createSequentialGroup()
						.addGap(38, 38, 38)
						.addComponent(pane,
								javax.swing.GroupLayout.PREFERRED_SIZE,
								javax.swing.GroupLayout.DEFAULT_SIZE,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addContainerGap(74, Short.MAX_VALUE)));

		pane.setVisible(false);
		this.add(pp, java.awt.BorderLayout.CENTER);

		init.setVisible(true);

		this.pack();
		this.setLocationRelativeTo(null);
		jButton1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {
				controller.buyUnit("S");
			}
		});
		jButton2.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {
				controller.buyUnit("P");
			}
		});
		jButton3.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {
				controller.buyUnit("A");
			}
		});
		jButton4.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {
				controller.buyUnit("K");
			}
		});

		jButton7.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {
				setVisibleFalse();
				if (model.cur == model.player1) {
					NewGame ng = null;
					try {
						ng = new NewGame(controller, model);
					} catch (IOException ex) {
						Logger.getLogger(NewGame.class.getName()).log(
								Level.SEVERE, null, ex);
					}
					ng.setVisible(true);
					model.setCur2();
				} else {
					try {
						ForsesOverview fo = new ForsesOverview(controller,
								model);
						fo.setVisible(true);
					} catch (IOException ex) {
						Logger.getLogger(NewGame.class.getName()).log(
								Level.SEVERE, null, ex);
					}
				}
			}
		});

	}

	private void setVisibleFalse() {
		this.setVisible(false);
	}

	@Override
	public void setName(String s) {
		controller.setNickname(s);
	}

	public void setPaneVisibleFalse() {
		pane.setVisible(true);
	}

	public NewGame() throws IOException {
		super("Expendables. New Game");
		initComponents();
	}

	public NewGame(Controller c, Model m) throws IOException {
		controller = c;
		model = m;
		initComponents();
	}

	/*
	 * @Override public void actionPerformed(ActionEvent e) { throw new
	 * UnsupportedOperationException("Not supported yet."); }
	 */

	private javax.swing.JButton jButton1;
	private javax.swing.JButton jButton2;
	private javax.swing.JButton jButton3;
	private javax.swing.JButton jButton4;
	private javax.swing.JButton jButton7;
	private javax.swing.JFrame jFrame1;
	private javax.swing.JFrame jFrame2;
	private javax.swing.JMenu jMenu1;
	private javax.swing.JMenu jMenu2;
	private javax.swing.JMenuBar jMenuBar1;
	private javax.swing.JPanel jPanel1;
	private MyLabel label1;
	private MyLabel label2;
	private MyField jTextField3;
	private MyField jTextField4;
	private MyField jTextField5;
	private MyField jTextField6;
	private MyJOptionPane error;

}
