import Link from 'next/link';
import styles from '../styles/NavBar.module.css';

export default function NavBar() {
  return (
    <nav className={styles.nav}>
      <Link href="/Tetris" className={styles.link}>Tetris</Link>
      <Link href="/RetroSnake" className={styles.link}>Retro Snake</Link>
      <Link href="/MineSweeper" className={styles.link}>Mine Sweeper</Link>
      <Link href="/" className={styles.link}>Home</Link>
    </nav>
  );
}
