import Head from 'next/head';
import Link from 'next/link';
import NavBar from '../components/NavBar';

export default function RetroSnakePage() {
  return (
    <>
      <Head>
        <title>Retro Snake – NKU Games</title>
      </Head>
      <NavBar />
      <main style={{ padding: '2rem' }}>
        <h1>Retro Snake</h1>
        <p>Classic snake game with a retro feel.</p>
        <Link href="/">← Back to Home</Link>
      </main>
    </>
  );
}
