import Head from 'next/head';
import Link from 'next/link';
import NavBar from '../components/NavBar';

export default function MineSweeperPage() {
  return (
    <>
      <Head>
        <title>Mine Sweeper – NKU Games</title>
      </Head>
      <NavBar />
      <main style={{ padding: '2rem' }}>
        <h1>Mine Sweeper</h1>
        <p>Puzzle game where you uncover safe tiles while avoiding mines.</p>
        <Link href="/">← Back to Home</Link>
      </main>
    </>
  );
}
