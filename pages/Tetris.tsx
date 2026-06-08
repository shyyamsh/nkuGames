import Head from 'next/head';
import Link from 'next/link';
import NavBar from '../components/NavBar';

export default function TetrisPage() {
  return (
    <>
      <Head>
        <title>Tetris – NKU Games</title>
      </Head>
      <NavBar />
      <main style={{ padding: '2rem' }}>
        <h1>Tetris</h1>
        <p>Classic falling‑block puzzle game.</p>
        <Link href="/">← Back to Home</Link>
      </main>
    </>
  );
}
