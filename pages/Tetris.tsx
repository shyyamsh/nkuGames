import Head from 'next/head';
import Link from 'next/link';
import NavBar from '../components/NavBar';
import TetrisGame from '../components/TetrisGame';

export default function TetrisPage() {
  return (
    <>
      <Head>
        <title>Tetris – NKU Games</title>
      </Head>
      <NavBar />
      <main style={{ padding: '2rem', display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
        <h1>Tetris</h1>
        <TetrisGame />
        <Link href="/">← Back to Home</Link>
      </main>
    </>
  );
}
