/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class Expendables extends JFrame {

	Field field;
	private boolean isFirst = true;

	// private Model model = new Model();
	// private Controller controller = new Controller(model);

	private void initComponents() throws IOException {

		this.setIconImage(ImageIO.read(new File("icon.jpg")));
		this.setResizable(false);
		this.setSize(800, 600);
		this.setBackground(Color.GRAY);
		JButton button = new JButton("New Game");

		button.setFont(new java.awt.Font("Tahoma", 1, 30));
		button.setOpaque(true);
		button.setContentAreaFilled(true);
		button.setBackground(Color.GRAY);
		button.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (isFirst) {
					setVisible(false);
					NewGame ng = null;
					try {
						ng = new NewGame();
					} catch (IOException ex) {
						Logger.getLogger(Expendables.class.getName()).log(
								Level.SEVERE, null, ex);
					}
					ng.setVisible(true);
				} else {
					setVisible(false);
					NewGame ng = null;
					try {
						ng = new NewGame();
					} catch (IOException ex) {
						Logger.getLogger(Expendables.class.getName()).log(
								Level.SEVERE, null, ex);
					}
					ng.setVisible(true);
					field.setVisible(false);
				}
			}

		});
		JButton button2 = new JButton("Load Game");
		button2.setFont(new java.awt.Font("Tahoma", 1, 30));
		button2.setOpaque(true);
		button2.setContentAreaFilled(true);
		button2.setBackground(Color.GRAY);
		button2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				LoadGame lg = null;
				try {
					lg = new LoadGame();
				} catch (IOException ex) {
					Logger.getLogger(Expendables.class.getName()).log(
							Level.SEVERE, null, ex);
				}
				lg.setVisible(true);
			}

		});
		JButton button3 = new JButton("Save Game");
		button3.setFont(new java.awt.Font("Tahoma", 1, 30));
		button3.setOpaque(true);
		button3.setContentAreaFilled(true);
		button3.setBackground(Color.GRAY);
		button3.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (isFirst) {
					JOptionPane.showMessageDialog(thisLink(),
							"There is no game to save.");
				} else {
					String list[] = new File("saves.").list();
					int length = list.length;
					// System.out.print(length);

					// aFile=new RandomAccessFile(arg,"rw");
					File save2 = new File("saves/" + "save"
							+ String.valueOf(length + 1) + ".txt");
					// RandomAccessFile save = new
					// RandomAccessFile("saves/"+"save"+String.valueOf(length+1)+".txt",
					// "rw");
					try {
						save2.createNewFile();
					} catch (IOException ex) {
						Logger.getLogger(Expendables.class.getName()).log(
								Level.SEVERE, null, ex);
					}
					try {
						RandomAccessFile save = new RandomAccessFile("saves/"
								+ "save" + String.valueOf(length + 1) + ".txt",
								"rw");
						try {

							int len = field.model.player1.army.size();
							save.writeBytes(java.util.Calendar.getInstance()
									.getTime() + "\n");
							for (int i = 0; i < len; i++) {
								save.writeBytes(field.model.player1.army.get(i)
										.getName() + "\n");
								save.writeBytes(field.model.player1.army.get(i).Health
										+ "\n");
								save.writeBytes(field.model.player1.army.get(i).x
										+ "\n");
								save.writeBytes(field.model.player1.army.get(i).y
										+ "\n");
							}
							save.writeBytes("next \n");
							for (int i = 0; i < len; i++) {
								save.writeBytes(field.model.player2.army.get(i)
										.getName() + "\n");
								save.writeBytes(field.model.player2.army.get(i).Health
										+ "\n");
								save.writeBytes(field.model.player2.army.get(i).x
										+ "\n");
								save.writeBytes(field.model.player2.army.get(i).y
										+ "\n");
							}
							save.writeBytes("end");
							JOptionPane.showMessageDialog(thisLink(),
									"Game was saved successfully");

						} catch (IOException ex) {
							Logger.getLogger(Expendables.class.getName()).log(
									Level.SEVERE, null, ex);
						}

					} catch (FileNotFoundException ex) {
						Logger.getLogger(Expendables.class.getName()).log(
								Level.SEVERE, null, ex);
					}

				}
			}

		});

		ImagePanel pp = new ImagePanel();
		try {
			pp.setImage(ImageIO.read(new File("Expendables.jpg")));
		} catch (IOException e) {
			e.printStackTrace();
		}

		JPanel pane = new JPanel();

		pane.setBackground(Color.GRAY);
		pane.setSize(800, 600);
		pane.setOpaque(false);

		javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(
				pane);
		pane.setLayout(jPanel1Layout);
		jPanel1Layout
				.setHorizontalGroup(jPanel1Layout
						.createParallelGroup(
								javax.swing.GroupLayout.Alignment.LEADING)
						.addGroup(
								jPanel1Layout
										.createSequentialGroup()
										.addGap(290, 290, 290)
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.TRAILING)
														.addComponent(
																button,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																223,
																javax.swing.GroupLayout.PREFERRED_SIZE)
														.addComponent(
																button2,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																223,
																javax.swing.GroupLayout.PREFERRED_SIZE)
														.addComponent(
																button3,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																223,
																javax.swing.GroupLayout.PREFERRED_SIZE))
										.addGap(290, 290, 290)));
		jPanel1Layout.setVerticalGroup(jPanel1Layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addGroup(
				jPanel1Layout
						.createSequentialGroup()
						.addGap(110, 110, 110)
						.addComponent(button,
								javax.swing.GroupLayout.PREFERRED_SIZE, 82,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(18, 18, 18)
						.addComponent(button2,
								javax.swing.GroupLayout.PREFERRED_SIZE, 82,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(18, 18, 18)
						.addComponent(button3,
								javax.swing.GroupLayout.PREFERRED_SIZE, 82,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addContainerGap(282, Short.MAX_VALUE)));

		pane.add(button);
		pane.add(button2);
		pane.add(button3);
		pane.setVisible(true);

		pp.add(pane, java.awt.BorderLayout.CENTER);
		pp.setBackground(Color.GRAY);
		pp.setPreferredSize(new Dimension(800, 600));

		this.add(pp, java.awt.BorderLayout.CENTER);
		this.pack();
		this.setLocationRelativeTo(null);
	}

	private Expendables thisLink() {
		return this;
	}

	public Expendables() throws IOException {
		super("Expendables");
		initComponents();
	}

	public Expendables(boolean b, Field f) throws IOException {
		field = f;
		isFirst = b;
		initComponents();
	}

	public static void main(String[] args) throws IOException {

		Expendables app = new Expendables();
		app.setVisible(true);

	}

}
