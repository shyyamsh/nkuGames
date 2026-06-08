import Image from 'next/image'
import Link from 'next/link'
import styles from '../styles/GameCard.module.css'

export interface GameCardProps {
  title: string
  description: string
  imageUrl: string
  link?: string
}

export default function GameCard({ title, description, imageUrl, link }: GameCardProps & { link?: string }) {
  const cardContent = (
    <div className={styles.card}>
      <Image src={imageUrl} alt={title} width={350} height={250} className={styles.image} />
      <h3>{title}</h3>
      <p>{description}</p>
    </div>
  );

  return link ? (
    <Link href={link} passHref>
      {cardContent}
    </Link>
  ) : cardContent;
}
