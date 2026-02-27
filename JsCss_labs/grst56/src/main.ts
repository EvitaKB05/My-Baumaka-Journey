import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  
  // Добавьте это перед app.listen()
  app.enableCors({
    origin: true,
    methods: 'GET,HEAD,PUT,PATCH,POST,DELETE',
    credentials: true
  });

  await app.listen(3000);
}
  await app.listen(3000); // Явное указание порта 3000
  console.log(`Server started on http://localhost:${port}`);
}

bootstrap().catch(err => {
  console.error('Server failed to start:', err);
  process.exit(1);
});